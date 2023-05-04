#ifndef M281_RELAY
#define M281_RELAY

#include "stm32l4xx_hal.h"


/**
 * @brief Initializes the relay, sets it to default state - open
 * 
 * @param relay Relay that should be initialized
 */
void m281_init(char pin_letter, uint8_t pin_number);

/**
 * @brief Closes/enables the relay
 * 
 */
void m281_enable(char pin_letter, uint8_t pin_number);

/**
 * @brief Opens/disables the relay
 * 
 */
void m281_disable(char pin_letter, uint8_t pin_number);

#endif  // ifndef M281_RELAY