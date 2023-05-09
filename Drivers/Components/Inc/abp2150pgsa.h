// Full name of the sensor is ABP2DANT150PGSA3XX
// Measures Pressure and Temperature

#ifndef ABP2150PGSA3
#define ABP2150PGSA3

#include "stm32l4xx_hal.h"
#include "errors.h"


/**
 * @brief Initializes the 150PGSA3
 * 
 * @param pin_letter GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 * @param hspi SPI that sensor is connected to
 * @return Errors Error status defined in errors.h
 */
Errors abp2150pgsa_init(char pin_letter, uint8_t pin_number, SPI_HandleTypeDef hspi);

/**
 * @brief Starts the measurement process of the device
 * 
 * @param pin_letter GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 * @param hspi SPI that sensor is connected to
 * @return Errors Error status defined in errors.h
 */
Errors abp2150pgsa_start_measure(char pin_letter, uint8_t pin_number, SPI_HandleTypeDef hspi);

/**
 * @brief Get if the device is busy measuring currently
 * 
 * @param pin_letter GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 * @param hspi SPI that sensor is connected to
 * @param busy 1 - device is currently doing a measurement | 0 - not measuring
 * @return Errors Error status defined in errors.h
 */
Errors abp2150pgsa_is_busy(char pin_letter, uint8_t pin_number, SPI_HandleTypeDef hspi, uint8_t *busy);

/**
 * @brief Get pressure and temperature data, pressure - bar | tempreature - celsius
 * 
 * @param pin_letter GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 * @param hspi SPI that sensor is connected to
 * @param return_data double[2] - double[0] = pressure, double[1] = temperature
 * @return Errors Error status defined in errors.h
 */
Errors abp2150pgsa_read_data(char pin_letter, uint8_t pin_number, SPI_HandleTypeDef hspi, double *return_data);

#endif  // ifndef ABP2150PGSA3