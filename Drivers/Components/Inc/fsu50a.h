#ifndef FSU50A
#define FSU50A

#include "stm32l4xx_hal.h"


/**
 * @brief Initializes the FSU50A
 * 
 * @param pin_letter GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 */
void fsu50a_init(char pin_letter, uint8_t pin_number);

/**
 * @brief Get the state of the switch, closed or open (liquid flowing or not)
 * 
 * @param pin_letter GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 * @return GPIO_PinState SET - liquid flowing ; RESET - not flowing
 */
GPIO_PinState fsu50a_is_set(char pin_letter, uint8_t pin_number);

#endif  // ifndef FSU50A