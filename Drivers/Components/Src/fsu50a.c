#include "fsu50a.h"
#include "commons.h"


void fsu50a_init(char pin_letter, uint8_t pin_number) {
    GPIO_TypeDef *GPIOx = select_gpiox(pin_letter);
    uint16_t GPIO_Pin = 1 << pin_number;

    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;     // TODO: Double check with documentation which pull mode needs to be used
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

GPIO_PinState fsu50a_is_set(char pin_letter, uint8_t pin_number) {
    GPIO_TypeDef *GPIOx = select_gpiox(pin_letter);
    uint16_t GPIO_Pin = 1 << pin_number;
    
    return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}
