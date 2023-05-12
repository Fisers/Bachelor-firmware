#ifndef MOTOR
#define MOTOR

#include "m281_relay.h"
#include "errors.h"


/**
 * @brief Add motor, initialize it, automaticaly assign ID to it
 * 
 * @param pin_letter GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 * @return Errors Error status defined in errors.h
 */
Errors motor_add(char pin_letter, uint8_t pin_number);

/**
 * @brief Removes the motor from the list
 * 
 * @param id Assigned ID of the motor
 * @return Errors Error status defined in errors.h
 */
Errors motor_remove(uint16_t id);

/**
 * @brief Enable motor
 * 
 * @param id Assigned ID of the motor
 * @return Errors Error status defined in errors.h
 */
Errors motor_enable(uint16_t id);

/**
 * @brief Disable the motor
 * 
 * @param id Assigned ID of the motor
 * @return Errors Error status defined in errors.h
 */
Errors motor_disable(uint16_t id);

#endif  // ifndef MOTOR
