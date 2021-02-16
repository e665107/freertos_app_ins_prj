#ifndef _BSP_TIM_H
#define _BSP_TIM_H

#include "bsp_hal.h"

#define TIM_CLK_ENABLE()              __HAL_RCC_TIM1_CLK_ENABLE()

#define CAPTURE_MODE

void bsp_tim_init(void);

void bsp_tim_on(void);

#endif /* _BSP_TIM_H */








