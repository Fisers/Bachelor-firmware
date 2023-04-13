#ifndef M281_RELAY
#define M281_RELAY

#include "stm32l4xx_hal.h"

typedef struct {
    GPIO_TypeDef* GPIOx;
    uint16_t GPIO_Pin;
} M281;



/**
 * @brief Initializes the relay, sets it to default state - open
 * 
 * @param GPIOx where x can be (A..H) to select the GPIO peripheral for STM32L4 family
 * @param GPIO_Pin specifies the pin where the relay is connected to.
 */
void m281_init(M281 relay);

/**
 * @brief Closes/enables the relay
 * 
 */
void m281_enable(M281 relay);

/**
 * @brief Opens/disables the relay
 * 
 */
void m281_disable(M281 relay);

#endif  // ifndef M281_RELAY