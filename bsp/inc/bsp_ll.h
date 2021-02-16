#ifndef BSP_LL_H
#define BSP_LL_H

#define STM32F4XX

#include "common.h"

#ifdef STM32F1XX
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_pwr.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_gpio.h"
#elif defined STM32F4XX
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_cortex.h"
#define IC_CLASS f4

#elif defined STM32F7XX
#define IC_CLASS f7

#elif defined STM32L1XX
#define IC_CLASS l1
#elif defined STM32L0XX
#define IC_CLASS l0

#elif defined STM32F0XX
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_gpio.h"
#endif // STM32L0XX



#endif /* BSP_LL_H */

