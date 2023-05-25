#include "valve.h"
#include "component_config.h"
#include "FreeRTOS.h"
#include "task.h"


typedef struct {
    uint8_t enabled;
    char port;
    uint8_t pin_number;
} Valve;

struct Valves {
    Valve valve[MAX_VALVES];
    int16_t last_index;
};
struct Valves valves = {.last_index = -1};


Errors valve_add(char port, uint8_t pin_number) {
    if(valves.last_index+1 > MAX_VALVES) return OUT_OF_RANGE;

    // Add valve to our list
    taskENTER_CRITICAL();
    valves.last_index++;
    uint16_t id = valves.last_index;
    valves.valve[id].enabled = 1;
    valves.valve[id].port = port;
    valves.valve[id].pin_number = pin_number;
    taskEXIT_CRITICAL();

    return m281_init(port, pin_number);
}

Errors valve_remove(uint16_t id) {
    if (id > valves.last_index) return OUT_OF_RANGE;
    if (valves.valve[id].enabled == 0) return DISABLED;

    // Disable valve
    taskENTER_CRITICAL();
    valves.valve[id].enabled = 0;
    taskEXIT_CRITICAL();

    return NO_ERROR;
}

Errors valve_enable(uint16_t id) {
    if (id > valves.last_index) return OUT_OF_RANGE;
    if (valves.valve[id].enabled == 0) return DISABLED;

    return m281_enable(valves.valve[id].port, valves.valve[id].pin_number);
}

Errors valve_disable(uint16_t id) {
    if (id > valves.last_index) return OUT_OF_RANGE;
    if (valves.valve[id].enabled == 0) return DISABLED;

    return m281_disable(valves.valve[id].port, valves.valve[id].pin_number);
}
