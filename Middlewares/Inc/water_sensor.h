#ifndef WATER_SENSOR
#define WATER_SENSOR

#include "sen0217_water_flow_sensor.h"


/**
 * @brief Add water sensor, initialize it, automaticaly assign ID to it
 * 
 * @param pin_letter GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 */
void water_sensor_add(char pin_letter, uint8_t pin_number);

/**
 * @brief Remove water sensor from the list, deinitialize the pin
 * 
 * @param id Assigned ID of the device
 * @return uint8_t Error status defined in errors.h
 */
uint8_t water_sensor_remove(uint16_t id);

/**
 * @brief Get liters that have flown through the sensor
 * 
 * @param id Assigned ID of the sensor
 * @return double fluid in liters
 */
double water_sensor_get_liters(uint16_t id);

void water_sensor_reset(uint16_t id);

#endif  // ifndef WATER_SENSOR
