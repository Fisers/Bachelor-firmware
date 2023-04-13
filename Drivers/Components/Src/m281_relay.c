#include "m281_relay.h"

void m281_init(M281 relay) {
    // Initialize the pin in case it wasn't already done
    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin = relay.GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(relay.GPIOx, &GPIO_InitStruct);

    // Set relay to be disabled
    HAL_GPIO_WritePin(relay.GPIOx, relay.GPIO_Pin, GPIO_PIN_RESET);
}

void m281_enable(M281 relay) {
    HAL_GPIO_WritePin(relay.GPIOx, relay.GPIO_Pin, GPIO_PIN_SET);
}

void m281_disable(M281 relay) {
    HAL_GPIO_WritePin(relay.GPIOx, relay.GPIO_Pin, GPIO_PIN_RESET);
}
