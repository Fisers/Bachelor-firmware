#ifndef WATER_SWITCH
#define WATER_SWITCH

#include "fsu50a.h"
#include "errors.h"


/**
 * @brief Add water switch, initialize it, automaticaly assign ID to it
 * 
 * @param pin_letter GPIOx where x is the character of GPIO port
 * @param pin_number PIN number of GPIO (0 to 15)
 * @return Errors Error status defined in errors.h
 */
Errors water_switch_add(char pin_letter, uint8_t pin_number, int16_t *assigned_id);

/**
 * @brief Removes the water switch
 * 
 * @param id Assigned ID of the sensor
 * @return Errors Error status defined in errors.h
 */
Errors water_switch_remove(uint16_t id);

/**
 * @brief Get status if there is liquid flowing through the switch
 * 
 * @param id Assigned ID of the sensor
 * @param is_flowing 0 - There is no water flowing, 1 - There is water flowing, 2 - An error occured
 * @return Errors Error status defined in errors.h
 */
Errors water_switch_is_flowing(uint16_t id, uint8_t *is_flowing);


#endif  // ifndef WATER_SWITCH
