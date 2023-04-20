#include "sen0217_water_flow_sensor.h"
#include "component_config.h"
#include "FreeRTOS.h"
#include "task.h"

typedef struct {
    double liters;
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin;
} WaterSensor;

struct WaterSensors {
    WaterSensor waterSensor[MAX_WATER_SENSORS];
    int16_t last_index;
};
struct WaterSensors waterSensors = {.last_index = -1};

void init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    // Initialize the pin in case it wasn't already done
    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);

    // Enable NVIC for our pin
    switch (GPIO_Pin)
    {
    case GPIO_PIN_0:
        HAL_NVIC_EnableIRQ(EXTI0_IRQn);
        break;
    case GPIO_PIN_1:
        HAL_NVIC_EnableIRQ(EXTI1_IRQn);
        break;
    case GPIO_PIN_2:
        HAL_NVIC_EnableIRQ(EXTI2_IRQn);
        break;
    case GPIO_PIN_3:
        HAL_NVIC_EnableIRQ(EXTI3_IRQn);
        break;
    case GPIO_PIN_4:
        HAL_NVIC_EnableIRQ(EXTI4_IRQn);
        break;
    case GPIO_PIN_5 ... GPIO_PIN_9:
        HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
        break;
    case GPIO_PIN_10 ... GPIO_PIN_15:
        HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
        break;
    default:
        break;
    }

    // Add sensor to our list
    taskENTER_CRITICAL();
    waterSensors.last_index++;
    uint16_t id = waterSensors.last_index;
    waterSensors.waterSensor[id].liters = 0;
    waterSensors.waterSensor[id].GPIOx = GPIOx;
    waterSensors.waterSensor[id].GPIO_Pin = GPIO_Pin;
    taskEXIT_CRITICAL();
}

double get_liters(uint16_t id) {
    if(id > waterSensors.last_index)
        return 0;

    return waterSensors.waterSensor[id].liters;
}

void reset_liters(uint16_t id) {
    if(id > waterSensors.last_index)
        return;

    waterSensors.waterSensor[id].liters = 0;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    for(int i = 0; i <= waterSensors.last_index; i++) {
        WaterSensor* waterSensor = &waterSensors.waterSensor[i];

        if(GPIO_Pin == waterSensor->GPIO_Pin && HAL_GPIO_ReadPin(waterSensor->GPIOx, waterSensor->GPIO_Pin) == GPIO_PIN_SET) {
            waterSensor->liters += 1.0 / 450.0;
            break;
        }
    }
}
