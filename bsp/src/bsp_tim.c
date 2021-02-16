#include "bsp_tim.h"
#include "bsp_led.h"
#include "tim1_app.h"

TIM_HandleTypeDef    TimHandle;
/* Prescaler declaration */
void bsp_tim_init()
{
    uint32_t uwPrescalerValue = 0;
    uwPrescalerValue = (uint32_t)(SystemCoreClock / 1000000) - 1;
    /* TIM Peripheral clock enable */
    TIM_CLK_ENABLE();
    TimHandle.Instance = TIM1;
    /* Initialize TIM1 peripheral as follows:
       + Period = 10000 - 1
       + Prescaler = (SystemCoreClock/10000) - 1
       + ClockDivision = 0
       + Counter direction = Up
       + 1Khz
       + ClockDivision 1:4分频
    */
    TimHandle.Init.Period            = 1000;
    TimHandle.Init.Prescaler         = uwPrescalerValue;
    TimHandle.Init.ClockDivision     = 0;
    TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
    TimHandle.Init.RepetitionCounter = 0;
    TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
    {
        /* Initialization Error */
        error_handler();
    }

    /*##-2- Configure the NVIC for TIMx ########################################*/
    /* Set the TIMx priority */
    HAL_NVIC_SetPriority(TIM1_UP_IRQn, 5, 0);
    /* Enable the TIMx global Interrupt */
    HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
#ifndef USE_RTOS
    bsp_tim_on();
#endif
}

void bsp_tim_on()
{
    if (HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
    {
        /* Starting Error */
        error_handler();
    }
}


void TIM1_UP_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TimHandle);
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /* int need_yield; */
    /* if (xSemaphoreGiveFromISR(b_semaphore, &need_yield) != pdPASS) { */
    /*     /\*     /\\* ESP_EARLY_LOGD(TAG, "timer queue overflow"); *\\/ *\/ */
    /*     return; */
    /* } */
    /* if (need_yield == pdTRUE) { */
    /*     /\* portSWITCH_CONTEXT(); *\/ */
    /*     /\* bsp_led_off(LED0); *\/ */
    /*     portYIELD(); */
    /* } */
    xSemaphoreGiveFromISR(b_semaphore, NULL);
}

