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
 * @brief Get liters that have flown through the sensor
 * 
 * @param id Assigned ID fo the sensor
 * @return double fluid in liters
 */
double water_sensor_get_liters(uint16_t id);

void water_sensor_reset(uint16_t id);

#endif  // ifndef WATER_SENSOR
