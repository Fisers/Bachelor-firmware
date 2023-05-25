#include <string.h>
#include "stm32l4xx_hal.h"
#include "cli_interface.h"
#include "component_config.h"
#include "printf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "ftoa.h"

#include "pressure_sensor.h"
#include "water_sensor.h"
#include "valve.h"
#include "motor.h"
#include "water_switch.h"


Errors global_error = NO_ERROR;

RTC_HandleTypeDef *rtc_handle;
UART_HandleTypeDef *uart_handle;
SPI_HandleTypeDef *spi_handle;

uint8_t UART1_rxBuffer[12] = {0};
uint8_t incomming_command[12] = {0};
uint8_t cmd_index = 0;

uint8_t device_to_add[3] = {0};

uint8_t system_status = 0; // Is system activated / initialization process ended / sending data

void send_response(Errors error, char *extra_data) {
    char response[32] = {0};
    if(strlen(extra_data) == 0) snprintf(response, 32, "%i\n", error);
    else snprintf(response, 32, "%i,%s\n", error, extra_data);
    
    HAL_UART_Transmit(uart_handle, (uint8_t*)response, 32, HAL_MAX_DELAY);
}

void send_error(Errors error) {
    send_response(error, "");
}

void reset_inc_command() {
    for(int i = 0; i < cmd_index; i++) {
        incomming_command[i] = 0x00;
    }
    cmd_index = 0;
}

Errors set_time() {
    RTC_TimeTypeDef time;
    time.Hours = incomming_command[1];
    time.Minutes = incomming_command[2];
    time.Seconds = incomming_command[3];

    HAL_StatusTypeDef HAL_Status;
    HAL_Status = HAL_RTC_SetTime(rtc_handle, &time, RTC_FORMAT_BIN);
    if(HAL_Status == HAL_OK) return NO_ERROR;
    else return MISC_ERROR;
}

Errors cli_init(UART_HandleTypeDef *hlpuart, RTC_HandleTypeDef *hrtc, SPI_HandleTypeDef *hspi) {
    HAL_UART_Receive_IT(hlpuart, UART1_rxBuffer, 1);
    rtc_handle = hrtc;
    uart_handle = hlpuart;
    spi_handle = hspi;

    return NO_ERROR;
}

Errors cli_handle_commands() {
    Errors error = NO_ERROR;
    switch (incomming_command[0])
    {
    case 0x10: // Time sync
        if(cmd_index < 4) break; 
        error = set_time();
        send_error(error);
        reset_inc_command();
        break;

    case 0x0A: // Start operation
        system_status = 1;
        send_error(NO_ERROR);
        reset_inc_command();
        break;

    case 0x05: // Add device
        if(cmd_index < 4) break;
        for(uint8_t i = 0; i < 3; i++) {
            device_to_add[i] = incomming_command[i+1];
        }
        reset_inc_command();
        break;

    case 0x07: // Status of valves and motor
        if(cmd_index < 5) break;
        for(uint8_t i = 0; i < 31; i++) {
            uint8_t is_enabled = (incomming_command[5-((i / 8)+1)] >> (i % 8)) & 1;
            if(is_enabled) error = valve_enable(i);
            else error = valve_disable(i);

            if (error == OUT_OF_RANGE) break;
            else if(error == DISABLED) continue;
        }
        uint8_t is_enabled = (incomming_command[1] >> 7) & 1;
        if(is_enabled) motor_enable(0);
        else motor_disable(0);
        send_error(NO_ERROR);
        reset_inc_command();
        break;

    case 0x03: // Reset water sensor
        if(cmd_index < 2) break;
        error = water_sensor_reset(incomming_command[1]);
        send_error(error);
        reset_inc_command();
        break;
    
    default:
        send_error(DOESNT_EXIST);
        reset_inc_command();
        break;
    }

    return NO_ERROR;
}

char msg[512];
Errors cli_send_readings() {
    if(!system_status) return NO_ERROR;

    
    RTC_TimeTypeDef sTime;
    HAL_RTC_GetTime(rtc_handle, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(rtc_handle, NULL, RTC_FORMAT_BIN);   // For some reason GetDate needs to be called afterwards to get actual time (https://stackoverflow.com/questions/47040039/stm32l4-rtc-hal-not-working)
    double secfrac = sTime.Seconds + (((double)(sTime.SecondFraction-sTime.SubSeconds)) / ((double)(sTime.SecondFraction+1)));
    char seconds_ms[8];
    ftoa(secfrac, seconds_ms, 3);
    taskENTER_CRITICAL(); 
    snprintf(msg, 512, "%d:%d:%s", sTime.Hours, sTime.Minutes, seconds_ms); // Add time to the CSV line
    taskEXIT_CRITICAL();

    

    Errors error = NO_ERROR;
    Errors temp_error = NO_ERROR;

    // Pressure sensors
    for(int i = 0; i < MAX_PRESSURE_SENSORS; i++) {
        double pressure, temperature = 0;
        char pressure_str[16], temperature_str[16];

        temp_error = pressure_sensor_get_pressure(i, &pressure);
        if(temp_error == DISABLED) continue;
        else if(temp_error == OUT_OF_RANGE) break;
        else if(temp_error != NO_ERROR) {
            error = temp_error;
            continue;
        }

        pressure_sensor_get_temp(i, &temperature);
        ftoa(pressure, pressure_str, 3);
        ftoa(temperature, temperature_str, 3);

        taskENTER_CRITICAL(); 
        snprintf(msg, 512, "%s,%s,%s", msg, pressure_str, temperature_str); // Add pressure sensors to the line
        taskEXIT_CRITICAL();
    }
    
    // Water sensors
    for(int i = 0; i < MAX_WATER_SENSORS; i++) {
        double liters = 0;
        char liter_str[16];

        temp_error = water_sensor_get_liters(i, &liters);
        if(temp_error == DISABLED) continue;
        if(temp_error == OUT_OF_RANGE) break;
        ftoa(liters, liter_str, 3);

        taskENTER_CRITICAL(); 
        snprintf(msg, 512, "%s,%s", msg, liter_str); // Add water sensors to the line
        taskEXIT_CRITICAL();
    }

    // Water switches
    for(int i = 0; i < MAX_WATER_SWITCHES; i++) {
        uint8_t is_flowing = 0;
        temp_error = water_switch_is_flowing(i, &is_flowing);
        if(temp_error == DISABLED) continue;
        if(temp_error == OUT_OF_RANGE) break;

        taskENTER_CRITICAL(); 
        snprintf(msg, 512, "%s,%d", msg, is_flowing); // Add water switches to the line
        taskEXIT_CRITICAL();
    }

    // Check global error
    if(global_error != NO_ERROR) error = global_error;

    taskENTER_CRITICAL(); 
    snprintf(msg, 512, "%s,%d\n", msg, error); // Add error and new line to the line
    taskEXIT_CRITICAL();
    HAL_UART_Transmit(uart_handle, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
    global_error = NO_ERROR;

    return NO_ERROR;
}

Errors cli_handle_add_device() {
    if(device_to_add[1] == 0) return NO_ERROR;

    Errors error = NO_ERROR;
    int16_t assigned_id = 0;
    char response_data[16] = {0};
    switch(device_to_add[0]) {
        case 0: // Valve
            error = valve_add(device_to_add[1], device_to_add[2]);
            break;

        case 1: // Pressure sensor
            error = pressure_sensor_add(device_to_add[1], device_to_add[2], *spi_handle, &assigned_id);
            if (error != NO_ERROR) break;

            double pressure, temperature = 0;
            char pressure_str[16], temperature_str[16];
            pressure_sensor_get_pressure(assigned_id, &pressure);
            pressure_sensor_get_temp(assigned_id, &temperature);
            ftoa(pressure, pressure_str, 3);
            ftoa(temperature, temperature_str, 3);
            taskENTER_CRITICAL();
            snprintf(response_data, 16, "%s,%s", pressure_str, temperature_str);
            taskEXIT_CRITICAL();

            break;

        case 2: // Water sensor
            error = water_sensor_add(device_to_add[1], device_to_add[2]);
            break;

        case 3: // water switch
            error = water_switch_add(device_to_add[1], device_to_add[2], &assigned_id);
            if (error != NO_ERROR) break;

            uint8_t is_flowing = 0;
            water_switch_is_flowing(assigned_id, &is_flowing);
            taskENTER_CRITICAL();
            snprintf(response_data, 16, "%d", is_flowing);
            taskEXIT_CRITICAL();
            break;

        case 4: // motor
            error = motor_add(device_to_add[1], device_to_add[2]);
            break;
    }
    for (int i = 0; i < sizeof(device_to_add); i++)
    {
        device_to_add[i] = 0;
    }

    send_response(error, response_data);
    return error;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *hlpuart)
{
    if(UART1_rxBuffer[0] == 0x0F && cmd_index == 0) {
        send_error(NO_ERROR);
        NVIC_SystemReset();
    }
    incomming_command[cmd_index++] = UART1_rxBuffer[0];
    cli_handle_commands();
    
    HAL_UART_Receive_IT(hlpuart, UART1_rxBuffer, 1);
}
