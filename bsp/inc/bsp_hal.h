#ifndef _BSP_HAL_H
#define _BSP_HAL_H

#include "app_config.h"

#ifdef STM32F1XX
#include "stm32f1xx_hal.h"
#elif defined STM32F4XX
#include "stm32f4xx_hal.h"
#elif defined STM32F7XX
#include "stm32f7xx_hal.h"
#elif defined STM32L1XX
#include "stm32l1xx_hal.h"
#endif // STM32F1XX


#endif /* _BSP_HAL_H */
