#include "water_switch.h"
#include "component_config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "errors.h"

typedef struct {
    uint8_t enabled;
    char pin_letter;
    uint8_t pin_number;
} WaterSwitch;

struct WaterSwitches {
    WaterSwitch waterSwitch[MAX_WATER_SWITCHES];
    int16_t last_index;
};
struct WaterSwitches waterSwitches = {.last_index = -1};

Errors water_switch_add(char pin_letter, uint8_t pin_number, int16_t *assigned_id) {
    if(waterSwitches.last_index+1 > MAX_WATER_SWITCHES) return OUT_OF_RANGE;

    // Add sensor to our list
    taskENTER_CRITICAL();
    waterSwitches.last_index++;
    uint16_t id = waterSwitches.last_index;
    waterSwitches.waterSwitch[id].enabled = 1;
    waterSwitches.waterSwitch[id].pin_letter = pin_letter;
    waterSwitches.waterSwitch[id].pin_number = pin_number;
    taskEXIT_CRITICAL();
    *assigned_id = id;

    return fsu50a_init(pin_letter, pin_number);
}

Errors water_switch_remove(uint16_t id) {
    if (id > waterSwitches.last_index) return OUT_OF_RANGE;

    taskENTER_CRITICAL();
    waterSwitches.waterSwitch[id].enabled = 0;
    taskEXIT_CRITICAL();

    return NO_ERROR;
}

Errors water_switch_is_flowing(uint16_t id, uint8_t *is_flowing) {
    if (id > waterSwitches.last_index) return OUT_OF_RANGE;
    if (waterSwitches.waterSwitch[id].enabled == 0) return DISABLED;

    GPIO_PinState pin_state = fsu50a_is_set(waterSwitches.waterSwitch[id].pin_letter, waterSwitches.waterSwitch[id].pin_number);
    if (pin_state == GPIO_PIN_SET) *is_flowing = 1;
    else *is_flowing = 0;

    return NO_ERROR;
}
