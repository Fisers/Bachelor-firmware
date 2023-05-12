#include "water_switch.h"
#include "component_config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "errors.h"

typedef struct {
    char pin_letter;
    uint8_t pin_number;
    uint8_t is_set;
} WaterSwitch;

struct WaterSwitches {
    WaterSwitch waterSwitch[MAX_WATER_SWITCHES];
    int16_t last_index;
};
struct WaterSwitches waterSwitches = {.last_index = -1};

void water_switch_add(char pin_letter, uint8_t pin_number) {
    fsu50a_init(pin_letter, pin_number);

    // Add sensor to our list
    taskENTER_CRITICAL();
    waterSwitches.last_index++;
    uint16_t id = waterSwitches.last_index;
    waterSwitches.waterSwitch[id].is_set = 0;
    waterSwitches.waterSwitch[id].pin_letter = pin_letter;
    waterSwitches.waterSwitch[id].pin_number = pin_number;
    taskEXIT_CRITICAL();
}

void water_switch_remove(uint16_t id) {
    if (id > waterSwitches.last_index) return;

    // Set everything to NULL for switch object
    taskENTER_CRITICAL();
    waterSwitches.waterSwitch[id].is_set = NULL;
    waterSwitches.waterSwitch[id].pin_letter = NULL;
    waterSwitches.waterSwitch[id].pin_number = NULL;
    taskEXIT_CRITICAL();
}

uint8_t water_switch_is_flowing(uint16_t id) {
    if (id > waterSwitches.last_index) return OUT_OF_RANGE;
    if (waterSwitches.waterSwitch[id].pin_letter == NULL) return DOESNT_EXIST;

    return waterSwitches.waterSwitch[id].is_set;
}
