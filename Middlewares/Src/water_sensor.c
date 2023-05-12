#include "water_sensor.h"
#include "commons.h"


void water_sensor_add(char pin_letter, uint8_t pin_number) {
    sen0217_init(pin_letter, pin_number);
}

uint8_t water_sensor_remove(uint16_t id) {
    return sen0217_deinit(id);
}

double water_sensor_get_liters(uint16_t id) {
    return sen0217_get_liters(id);
}

void water_sensor_reset(uint16_t id) {
    sen0217_reset_liters(id);
}
