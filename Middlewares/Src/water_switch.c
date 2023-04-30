#include "water_switch.h"
#include "component_config.h"

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

}

void water_switch_remove(uint16_t id) {

}

uint8_t water_switch_is_flowing(uint16_t id) {
    return 0;
}
