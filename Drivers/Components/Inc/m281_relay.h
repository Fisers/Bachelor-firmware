#ifndef M281_RELAY
#define M281_RELAY

#include "stm32l4xx_hal.h"
#include "errors.h"


/**
 * @brief Initializes the relay, sets it to default state - open
 * 
 * @param relay Relay that should be initialized
 * @return Errors Error status defined in errors.h 
 */
Errors m281_init(char pin_letter, uint8_t pin_number);

/**
 * @brief Closes/enables the relay
 * 
 * @return Errors Error status defined in errors.h 
 */
Errors m281_enable(char pin_letter, uint8_t pin_number);

/**
 * @brief Opens/disables the relay
 * 
 * @return Errors Error status defined in errors.h 
 */
Errors m281_disable(char pin_letter, uint8_t pin_number);

#endif  // ifndef M281_RELAY