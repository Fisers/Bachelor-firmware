#ifndef FSU50A
#define FSU50A

#include "stm32l4xx_hal.h"


/**
 * @brief Initializes the FSU50A
 * 
 * @param GPIOx 
 * @param GPIO_Pin 
 */
void init(char pin_letter, uint8_t pin_number);

GPIO_PinState is_set(char pin_letter, uint8_t pin_number);

#endif  // ifndef FSU50A