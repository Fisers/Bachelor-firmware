#include "commons.h"

GPIO_TypeDef* select_gpiox(char port) {
    switch (port)
    {
    case 'A':
        return GPIOA;
    case 'B':
        return GPIOB;
    case 'C':
        return GPIOC;
    case 'D':
        return GPIOD;
    case 'E':
        return GPIOE;
    case 'F':
        return GPIOF;
    case 'G':
        return GPIOG;
    case 'H':
        return GPIOH;
    case 'I':
        return GPIOI;
    
    default:
        return NULL;
    }
}
