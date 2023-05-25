#ifndef WATER_SENSOR
#define WATER_SENSOR

#include "sen0217_water_flow_sensor.h"
#include "errors.h"


/**
 * @brief Add water sensor, initialize it, automaticaly assign ID to it
 * 
 * @param port GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 * @return Errors Error status defined in errors.h
 */
Errors water_sensor_add(char port, uint8_t pin_number);

/**
 * @brief Remove water sensor from the list, deinitialize the pin
 * 
 * @param id Assigned ID of the device
 * @return Errors Error status defined in errors.h
 */
Errors water_sensor_remove(uint16_t id);

/**
 * @brief Get liters that have flown through the sensor
 * 
 * @param id Assigned ID of the sensor
 * @param liters double fluid in liters
 * @return Errors Error status defined in errors.h
 */
Errors water_sensor_get_liters(uint16_t id, double *liters);

/**
 * @brief Reset liter counter back to 0
 * 
 * @param id Assigned ID of the device
 * @return Errors Error status defined in errors.h
 */
Errors water_sensor_reset(uint16_t id);

#endif  // ifndef WATER_SENSOR
