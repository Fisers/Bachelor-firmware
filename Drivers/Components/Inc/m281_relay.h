#ifndef M281_RELAY
#define M281_RELAY

#include "stm32l4xx_hal.h"
#include "errors.h"


/**
 * @brief Initializes the relay, sets it to default state - open
 * 
 * @param port GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 * @return Errors Error status defined in errors.h 
 */
Errors m281_init(char port, uint8_t pin_number);

/**
 * @brief Closes/enables the relay
 * 
 * @param port GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 * @return Errors Error status defined in errors.h 
 */
Errors m281_enable(char port, uint8_t pin_number);

/**
 * @brief Opens/disables the relay
 * 
 * @param port GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 * @return Errors Error status defined in errors.h 
 */
Errors m281_disable(char port, uint8_t pin_number);

#endif  // ifndef M281_RELAY