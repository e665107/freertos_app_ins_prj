#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "tim1_app.h"
#include "stdio.h" 

#include "bsp_tim.h"
#include "bsp_led.h"


#define TIM_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

static void tim_task(void *parameter);

static TickType_t delay_ms = 1000 / portTICK_PERIOD_MS;
static TickType_t delay_100ms = 100 / portTICK_PERIOD_MS;

SemaphoreHandle_t b_semaphore;

#ifdef TIM_TEST_APP
void tim_task_create(uint8_t priority_1)
{
    xTaskCreate(tim_task, "tim_process", TIM_TASK_STACK_SIZE, NULL, priority_1, (TaskHandle_t)NULL);
}

static void tim_task(void *parameter)
{
    b_semaphore = xSemaphoreCreateBinary();
    bsp_tim_on();  

    for(;;) {
        xSemaphoreTake(b_semaphore, portMAX_DELAY);
        bsp_led_toggle(LED0);
        /* vTaskDelay(delay_100ms); */
    }
}

#endif












