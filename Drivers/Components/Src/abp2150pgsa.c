#include "abp2150pgsa.h"
#include "commons.h"
#include "FreeRTOS.h"
#include "task.h"


#define MAX_TRIES 5
// SPI commands
uint8_t get_status[1] = {0xF0};
uint8_t start_measurement[3] = {0xAA, 0x00, 0x00};
uint8_t get_measurement[7] = {0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

Errors abp2150pgsa_init(char port, uint8_t pin_number, SPI_HandleTypeDef hspi) {
    GPIO_TypeDef *GPIOx = select_gpiox(port);
    uint16_t GPIO_Pin = 1 << pin_number;

    // Init CS pin
    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);

    // Test if device connected and powered on
    uint8_t status = 0xFF;
    uint8_t tries = 0;
    do {
      HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
      HAL_SPI_TransmitReceive(&hspi, (uint8_t*)get_status, &status, sizeof(get_status), HAL_MAX_DELAY);
      HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);

      tries++;
      vTaskDelay(10 / portTICK_PERIOD_MS);
    } while(!(0x40 & status) && tries <= MAX_TRIES);

    if(tries >= MAX_TRIES) return DOESNT_EXIST;

    return NO_ERROR;
}


Errors abp2150pgsa_start_measure(char port, uint8_t pin_number, SPI_HandleTypeDef hspi) {
    GPIO_TypeDef *GPIOx = select_gpiox(port);
    uint16_t GPIO_Pin = 1 << pin_number;

    uint8_t return_data[sizeof(start_measurement)];
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi, (uint8_t*)start_measurement, (uint8_t*)return_data, sizeof(start_measurement), HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);

    if(!(0x40 & return_data[0])) return DOESNT_EXIST;

    return NO_ERROR;
}


Errors abp2150pgsa_is_busy(char port, uint8_t pin_number, SPI_HandleTypeDef hspi, uint8_t *busy) {
    GPIO_TypeDef *GPIOx = select_gpiox(port);
    uint16_t GPIO_Pin = 1 << pin_number;

    uint8_t status = 0xFF;
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi, (uint8_t*)get_status, &status, sizeof(get_status), HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);

    if(status == 0xFF || !(0x40 & status)) return DOESNT_EXIST;

    *busy = 0x20 & status;

    return NO_ERROR;
}


Errors abp2150pgsa_read_data(char port, uint8_t pin_number, SPI_HandleTypeDef hspi, double *return_data) {
    GPIO_TypeDef *GPIOx = select_gpiox(port);
    uint16_t GPIO_Pin = 1 << pin_number;

    uint8_t response[7] = {0x00};
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi, (uint8_t*)get_measurement, (uint8_t*)response, sizeof(get_measurement), HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);

    uint32_t press_count = (response[1] << 16) + (response[2] << 8) + response[3];
    uint32_t temp_count = (response[4] << 16) + (response[5] << 8) + response[6];

    return_data[0] = (double)(press_count * 150)/(double)16777215;
    return_data[1] = ((double)(temp_count * 200)/(double)16777215) - 50;

    return NO_ERROR;
}
