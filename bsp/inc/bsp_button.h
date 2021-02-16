#ifndef _BSP_BUTTON_H
#define _BSP_BUTTON_H

#include "bsp_hal.h"

void bsp_button_init(void);
uint8_t bsp_button_in(GPIO_TypeDef* gpio, uint16_t pin);


#endif /* _BSP_BUTTON_H */
