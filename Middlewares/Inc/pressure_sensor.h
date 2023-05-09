#ifndef PRESSURE_SENSOR
#define PRESSURE_SENSOR

#include "abp2150pgsa.h"
#include "errors.h"


/**
 * @brief Add pressure sensor, initialize it, automaticaly assign ID to it
 * 
 * @param pin_letter GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 * @return Errors Error status defined in errors.h
 */
Errors pressure_sensor_add(char pin_letter, uint8_t pin_number, SPI_HandleTypeDef hspi);

/**
 * @brief Removes the water switch
 * 
 * @param id Assigned ID of the sensor
 * @return Errors Error status defined in errors.h
 */
Errors pressure_sensor_remove(uint16_t id);

/**
 * @brief Reads data from the sensor (pressure and temperature), stores it locally
 * 
 * @param id Assigned ID of the sensor
 * @return Errors Error status defined in errors.h
 */
Errors pressure_sensor_read_data(uint16_t id);

/**
 * @brief pressure_sensor_read_data needs to be called first, returns pressure from the reading
 * 
 * @param id Assigned ID of the sensor
 * @param pressure return pressure of the sensor in PSI
 * @return Errors Error status defined in errors.h
 */
Errors pressure_sensor_get_pressure(uint16_t id, double *pressure);

/**
 * @brief pressure_sensor_read_data needs to be called first, returns temperature from the reading
 * 
 * @param id Assigned ID of the sensor
 * @param temp return temperature of the sensor in celsius
 * @return Errors Error status defined in errors.h
 */
Errors pressure_sensor_get_temp(uint16_t id, double *temp);


#endif  // ifndef PRESSURE_SENSOR
