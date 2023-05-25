#ifndef SEN0217_WATER_FLOW_SENSOR
#define SEN0217_WATER_FLOW_SENSOR

#include "stm32l4xx_hal.h"
#include "errors.h"


/**
 * @brief Initialize SEN0217 water flow sensor, enable interrupts
 * 
 * @param port GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 * @return Errors Error status defined in errors.h 
 */
Errors sen0217_init(char port, uint8_t pin_number);

/**
 * @brief Deinitializes SEN0217 water flwo sensor, disables interrupts
 * 
 * @param id Assigned ID of the device
 * @return Errors Error status defined in errors.h
 */
Errors sen0217_deinit(uint16_t id);

/**
 * @brief Get liters that have flown through
 * 
 * @param id Assigned ID of the device
 * @param liters double Liters with precision down to .002 L
 * @return Errors Error status defined in errors.h 
 */
Errors sen0217_get_liters(uint16_t id, double *liters);

/**
 * @brief Reset flown liters back to 0
 * 
 * @param id Assigned ID of the device
 * @return Errors Error status defined in errors.h 
 */
Errors sen0217_reset_liters(uint16_t id);

#endif  // ifndef SEN0217_WATER_FLOW_SENSOR