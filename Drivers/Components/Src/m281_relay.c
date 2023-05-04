#include "m281_relay.h"

void m281_init(char pin_letter, uint8_t pin_number) {
    GPIO_TypeDef *GPIOx = select_gpiox(pin_letter);
    uint16_t GPIO_Pin = 1 << pin_number;

    // Initialize the pin in case it wasn't already done
    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

    // Set relay to be disabled
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
}

void m281_enable(char pin_letter, uint8_t pin_number) {
    GPIO_TypeDef *GPIOx = select_gpiox(pin_letter);
    uint16_t GPIO_Pin = 1 << pin_number;

    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
}

void m281_disable(char pin_letter, uint8_t pin_number) {
    GPIO_TypeDef *GPIOx = select_gpiox(pin_letter);
    uint16_t GPIO_Pin = 1 << pin_number;

    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
}
