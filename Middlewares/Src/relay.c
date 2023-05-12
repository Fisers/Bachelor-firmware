#include "relay.h"
#include "component_config.h"
#include "FreeRTOS.h"
#include "task.h"
#include "errors.h"


typedef struct {
    char pin_letter;
    uint8_t pin_number;
} Relay;

struct Relays {
    Relay relay[MAX_RELAYS];
    int16_t last_index;
};
struct Relays relays = {.last_index = -1};


void relay_add(char pin_letter, uint8_t pin_number) {
    m281_init(pin_letter, pin_number);

    // Add relay to our list
    taskENTER_CRITICAL();
    relays.last_index++;
    uint16_t id = relays.last_index;
    relays.relay[id].pin_letter = pin_letter;
    relays.relay[id].pin_number = pin_number;
    taskEXIT_CRITICAL();
}

uint8_t relay_remove(uint16_t id) {
    if (id > relays.last_index) return OUT_OF_RANGE;
    if (relays.relay[id].pin_letter == NULL) return DOESNT_EXIST;

    // Set everything to NULL for relay object
    taskENTER_CRITICAL();
    relays.relay[id].pin_letter = NULL;
    relays.relay[id].pin_number = NULL;
    taskEXIT_CRITICAL();

    return NO_ERROR;
}

uint8_t relay_enable(uint16_t id) {
    if (id > relays.last_index) return OUT_OF_RANGE;
    if (relays.relay[id].pin_letter == NULL) return DOESNT_EXIST;

    m281_enable(relays.relay[id].pin_letter, relays.relay[id].pin_number);
    return NO_ERROR;
}

uint8_t relay_disable(uint16_t id) {
    if (id > relays.last_index) return OUT_OF_RANGE;
    if (relays.relay[id].pin_letter == NULL) return DOESNT_EXIST;

    m281_disable(relays.relay[id].pin_letter, relays.relay[id].pin_number);
    return NO_ERROR;
}
