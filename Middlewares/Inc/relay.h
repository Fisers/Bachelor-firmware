#ifndef RELAY
#define RELAY

#include "m281_relay.h"


/**
 * @brief Add relay, initialize it, automaticaly assign ID to it
 * 
 * @param pin_letter GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 */
void relay_add(char pin_letter, uint8_t pin_number);

/**
 * @brief Removes the relay from the list
 * 
 * @param id Assigned ID of the relay
 * @return uint8_t Error message defined in errors.h
 */
uint8_t relay_remove(uint16_t id);

/**
 * @brief Enable relay
 * 
 * @param id Assigned ID of the relay
 * @return Error message defined in errors.h
 */
uint8_t relay_enable(uint16_t id);

/**
 * @brief Disable the relay
 * 
 * @param id Assigned ID of the relay
 * @return Error message defined in errors.h
 */
uint8_t relay_disable(uint16_t id);

#endif  // ifndef RELAY
