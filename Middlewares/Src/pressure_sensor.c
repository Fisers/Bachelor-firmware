#include "pressure_sensor.h"
#include "component_config.h"
#include "FreeRTOS.h"
#include "task.h"


uint8_t MAX_TRIES = 5;

typedef struct {
    uint8_t enabled;
    char pin_letter;
    uint8_t pin_number;
    SPI_HandleTypeDef hspi;
    double pressure;
    double temperature;
} PressureSensor;
struct PressureSensors {
    PressureSensor pressureSensor[MAX_PRESSURE_SENSORS];
    int16_t last_index;
};
struct PressureSensors pressureSensors = {.last_index = -1};

Errors pressure_sensor_add(char pin_letter, uint8_t pin_number, SPI_HandleTypeDef hspi, int16_t *assigned_id) {
    if(pressureSensors.last_index+1 > MAX_PRESSURE_SENSORS) return OUT_OF_RANGE;

    Errors error = abp2150pgsa_init(pin_letter, pin_number, hspi);
    if(error != NO_ERROR) return error;

    // Add sensor to our list
    taskENTER_CRITICAL();
    pressureSensors.last_index++;
    uint16_t id = pressureSensors.last_index;
    pressureSensors.pressureSensor[id].enabled = 1;
    pressureSensors.pressureSensor[id].pin_letter = pin_letter;
    pressureSensors.pressureSensor[id].pin_number = pin_number;
    pressureSensors.pressureSensor[id].hspi = hspi;
    pressureSensors.pressureSensor[id].pressure = 0;
    pressureSensors.pressureSensor[id].temperature = 0;
    taskEXIT_CRITICAL();
    *assigned_id = id;

    return NO_ERROR;
}

Errors pressure_sensor_remove(uint16_t id) {
    if (id > pressureSensors.last_index) return OUT_OF_RANGE;

    // Disable sensor in list
    taskENTER_CRITICAL();
    pressureSensors.pressureSensor[id].enabled = 0;
    taskEXIT_CRITICAL();

    return NO_ERROR;
}

Errors pressure_sensor_read_data(uint16_t id) {
    if (id > pressureSensors.last_index) return OUT_OF_RANGE;
    if (pressureSensors.pressureSensor[id].enabled == 0) return DISABLED;

    Errors error = NO_ERROR;
    PressureSensor *pressureSensor = &pressureSensors.pressureSensor[id];
    // Start measurement process
    error = abp2150pgsa_start_measure(pressureSensor->pin_letter, pressureSensor->pin_number, pressureSensor->hspi);
    if (error != NO_ERROR) {
        pressureSensor->pressure = 0;
        pressureSensor->temperature = 0;
        return error;
    }

    // Read status of the sensor and wait for it to not be busy
    uint8_t is_busy = 1;
    uint8_t tries = 0;
    while(is_busy && tries < MAX_TRIES) {
        vTaskDelay(10 / portTICK_PERIOD_MS); // Wait and make sure measurement is done
        error = abp2150pgsa_is_busy(pressureSensor->pin_letter, pressureSensor->pin_number, pressureSensor->hspi, &is_busy);
        if (error != NO_ERROR) {
            pressureSensor->pressure = 0;
            pressureSensor->temperature = 0;
            return error;
        }

        tries++;
    }
    if (tries >= MAX_TRIES) {
        pressureSensor->pressure = 0;
        pressureSensor->temperature = 0;
        return TRIES_EXCEEDED;
    };

    // Read data from the sensor
    double return_data[2] = {0};
    error = abp2150pgsa_read_data(pressureSensor->pin_letter, pressureSensor->pin_number, pressureSensor->hspi, return_data);
    if (error != NO_ERROR) {
        pressureSensor->pressure = 0;
        pressureSensor->temperature = 0;
        return error;
    }

    pressureSensor->pressure = return_data[0];
    pressureSensor->temperature = return_data[1];

    return NO_ERROR;
}

Errors pressure_sensor_get_pressure(uint16_t id, double *pressure) {
    if (id > pressureSensors.last_index) return OUT_OF_RANGE;
    if (pressureSensors.pressureSensor[id].enabled == 0) return DISABLED;

    *pressure = pressureSensors.pressureSensor[id].pressure;
    return NO_ERROR;
}

Errors pressure_sensor_get_temp(uint16_t id, double *temp) {
    if (id > pressureSensors.last_index) return OUT_OF_RANGE;
    if (pressureSensors.pressureSensor[id].enabled == 0) return DISABLED;

    *temp = pressureSensors.pressureSensor[id].temperature;
    return NO_ERROR;
}
