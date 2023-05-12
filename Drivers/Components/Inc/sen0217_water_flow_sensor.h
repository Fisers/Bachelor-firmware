#ifndef SEN0217_WATER_FLOW_SENSOR
#define SEN0217_WATER_FLOW_SENSOR

#include "stm32l4xx_hal.h"


/**
 * @brief Initialize SEN0217 water flow sensor, enable interrupts
 * 
 * @param pin_letter GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 */
void sen0217_init(char pin_letter, uint8_t pin_number);

/**
 * @brief Deinitializes SEN0217 water flwo sensor, disables interrupts
 * 
 * @param id Assigned ID of the device
 * @return uint8_t Error status defined in errors.h
 */
uint8_t sen0217_deinit(uint16_t id);

/**
 * @brief Get liters that have flown through
 * 
 * @param id Assigned ID of the device
 * @return double Liters with precision down to .002 L
 */
double sen0217_get_liters(uint16_t id);

/**
 * @brief Reset flown liters back to 0
 * 
 * @param id Assigned ID of the device
 */
void sen0217_reset_liters(uint16_t id);

#endif  // ifndef SEN0217_WATER_FLOW_SENSOR