/* os */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* lib */
#include "stdio.h"
#include "common.h"

/* app */
#include "list_task.h"

/* bsp */
/* #include "bsp_bsp_name.h" */

/* func */
#include ".h"

#define TEMPLATE_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

static void app_name_task(void *parameter);

static TickType_t delay_100ms = 100 / portTICK_PERIOD_MS;

void app_name_task_create(uint8_t priority_1)
{
    xTaskCreate(app_name_task, "app_name_process", app_name_TASK_STACK_SIZE, NULL, priority_1, (TaskHandle_t)NULL);
}

static void app_name_task(void *parameter)
{
    static uint8_t state = 0;
    
    static uint8_t time_cnt_temp = 0;
    
    (void) parameter;
    
    for (;;)
    {
        switch (state)
        {
            case 0:
                
                state = 1;
                break;
                
            case 1:
                
                state = 2;
                
                break;
                
            case 2:
                
                break;
                
            default:
                break;
        }
        vTaskDelay(100);
        time_cnt_temp++;
    }
}

















 
