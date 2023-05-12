#include "motor.h"
#include "component_config.h"
#include "FreeRTOS.h"
#include "task.h"


typedef struct {
    uint8_t enabled;
    char pin_letter;
    uint8_t pin_number;
} Motor;

struct Motors {
    Motor motor[MAX_MOTORS];
    int16_t last_index;
};
struct Motors motors = {.last_index = -1};


Errors motor_add(char pin_letter, uint8_t pin_number) {
    if(motors.last_index+1 > MAX_MOTORS) return OUT_OF_RANGE;

    // Add motor to our list
    taskENTER_CRITICAL();
    motors.last_index++;
    uint16_t id = motors.last_index;
    motors.motor[id].enabled = 1;
    motors.motor[id].pin_letter = pin_letter;
    motors.motor[id].pin_number = pin_number;
    taskEXIT_CRITICAL();

    return m281_init(pin_letter, pin_number);
}

Errors motor_remove(uint16_t id) {
    if (id > motors.last_index) return OUT_OF_RANGE;
    if (motors.motor[id].enabled == 0) return DISABLED;

    // Disable motor
    taskENTER_CRITICAL();
    motors.motor[id].enabled = 0;
    taskEXIT_CRITICAL();

    return NO_ERROR;
}

Errors motor_enable(uint16_t id) {
    if (id > motors.last_index) return OUT_OF_RANGE;
    if (motors.motor[id].enabled == 0) return DISABLED;

    return m281_enable(motors.motor[id].pin_letter, motors.motor[id].pin_number);
}

Errors motor_disable(uint16_t id) {
    if (id > motors.last_index) return OUT_OF_RANGE;
    if (motors.motor[id].enabled == 0) return DISABLED;

    return m281_disable(motors.motor[id].pin_letter, motors.motor[id].pin_number);
}
