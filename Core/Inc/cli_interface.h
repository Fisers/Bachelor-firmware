#ifndef CLI_INTERFACE
#define CLI_INTERFACE

#include "stm32l496xx.h"
#include "errors.h"


/**
 * Device types:
 * 0 - valve
 * 1 - pressure sensor
 * 2 - liquid counter
 * 3 - liquid switch
 * 4 - motor
 */
/**
 * Commands line interface using UART, available commands are:
 * 0x10 - Time sync (0x10 hour minute second)
 * 0x05 - Add device (0x05 device_type GPIOx PIN)
 * 0x0A - Start operation / sending data
 * 0x07 - Status of the valves / motor (0x07 4bytes)
 * 0x03 - Reset liquid counter (0x03 id_of_water_sensor)
 * 0x0F - Restart controller
 */

extern Errors global_error;
extern uint8_t system_status;


Errors cli_init(UART_HandleTypeDef *hlpuart, RTC_HandleTypeDef *hrtc, SPI_HandleTypeDef *hspi);

Errors cli_handle_commands();

Errors cli_send_readings();

Errors cli_handle_add_device();

#endif