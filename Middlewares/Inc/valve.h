#ifndef VALVE
#define VALVE

#include "m281_relay.h"
#include "errors.h"


/**
 * @brief Add valve, initialize it, automaticaly assign ID to it
 * 
 * @param port GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 * @return Errors Error status defined in errors.h
 */
Errors valve_add(char port, uint8_t pin_number);

/**
 * @brief Removes the valve from the list
 * 
 * @param id Assigned ID of the valve
 * @return Errors Error status defined in errors.h
 */
Errors valve_remove(uint16_t id);

/**
 * @brief Enable valve
 * 
 * @param id Assigned ID of the valve
 * @return Errors Error status defined in errors.h
 */
Errors valve_enable(uint16_t id);

/**
 * @brief Disable the valve
 * 
 * @param id Assigned ID of the valve
 * @return Errors Error status defined in errors.h
 */
Errors valve_disable(uint16_t id);

#endif  // ifndef VALVE
