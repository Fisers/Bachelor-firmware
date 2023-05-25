#include "water_sensor.h"
#include "commons.h"


Errors water_sensor_add(char port, uint8_t pin_number) {
    return sen0217_init(port, pin_number);
}

Errors water_sensor_remove(uint16_t id) {
    return sen0217_deinit(id);
}

Errors water_sensor_get_liters(uint16_t id, double *liters) {
    return sen0217_get_liters(id, liters);
}

Errors water_sensor_reset(uint16_t id) {
    return sen0217_reset_liters(id);
}
