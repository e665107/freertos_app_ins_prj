/* os */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* lib */
#include "stdio.h"
#include "common.h"

/* app */
#include "task_t.h"
#include "freertos_func_test.h"
/* bsp */
#include "bsp_uart.h"


/* func */
/* #include "func_name_f.h" */

#define TASK_T_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

static void task_t_task(void *parameter);
static void task1_t_task(void *parameter);

static TickType_t delay_100ms = 100 / portTICK_PERIOD_MS;

static TaskHandle_t xTask_t = NULL, xTask1_t = NULL;
void task_t_task_create(uint8_t priority_1)
{
    xTaskCreate(task_t_task, "task_t_process", TASK_T_TASK_STACK_SIZE, NULL, priority_1, (TaskHandle_t)&xTask_t);
    xTaskCreate(task1_t_task, "task1_t_process", TASK_T_TASK_STACK_SIZE, NULL, priority_1+1, (TaskHandle_t)&xTask1_t);

}

static void task_t_task(void *parameter)
{
    static uint8_t state = 0;
    
    static uint8_t time_cnt_temp = 0;
    uint32_t ulEventsToProcess;
    (void) parameter;
    
    for (;;)
    {

        ulEventsToProcess = ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
        if(ulEventsToProcess !=0 )
        {
            while( ulEventsToProcess > 0 )
            {
                printf( "Handler task - Processing event.\r\n" );
                ulEventsToProcess--;
                xTaskNotifyGive(xTask1_t);

            }


        }
        else
        {


        }
        
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


static void task1_t_task(void *parameter)
{
    static uint8_t state = 0;
    
    static uint8_t time_cnt_temp = 0;

    (void) parameter;
    
    for (;;)
    {
        xTaskNotifyGive(xTask_t);
        
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        
        switch (state)
        {
            case 0:
                
 
                break;

            case 1:
                
                state = 2;
                
                break;

            case 2:

                break;

            default:
                break;
        }
        vTaskDelay(2000);
        time_cnt_temp++;
    }
}
















