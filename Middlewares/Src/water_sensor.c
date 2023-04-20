#include "water_sensor.h"
#include "commons.h"


void water_sensor_add(char pin_letter, uint8_t pin_number) {
    GPIO_TypeDef *GPIOx = select_gpiox(pin_letter);
    uint16_t GPIO_Pin = 1 << pin_number;

    init(GPIOx, GPIO_Pin);
}

double water_sensor_get_liters(uint16_t id) {
    return get_liters(id);
}

void water_sensor_reset(uint16_t id) {
    reset_liters(id);
}
