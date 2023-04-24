#ifndef SEN0217_WATER_FLOW_SENSOR
#define SEN0217_WATER_FLOW_SENSOR

#include "stm32l4xx_hal.h"


/**
 * @brief Initializes the water flow sensor to measure water flow using interrupts on selected PIN
 * 
 * @param water_flow_sensor Sensor that should be initialized
 */
void init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

double get_liters(uint16_t id);

void reset_liters(uint16_t id);

#endif  // ifndef SEN0217_WATER_FLOW_SENSOR