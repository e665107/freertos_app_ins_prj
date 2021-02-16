/* os */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"

/* lib */
#include "stdio.h"
#include "common.h"

/* app */
#include "timer_t.h"
#include "freertos_func_test.h"

/* bsp */
#include "bsp_uart.h"

 
/* func */
/* #include "func_name_f.h" */

#define TIMER_TASK_STACK_SIZE  configMINIMAL_STACK_SIZE
#define NUM_TIMERS    5

static void timer_task(void *parameter);
void timer_creat_init(void);
void vTimerCallback( TimerHandle_t xTimer );

static TickType_t delay_100ms = 100 / portTICK_PERIOD_MS;

TimerHandle_t xTimers[NUM_TIMERS];

void timer_task_create(uint8_t priority_1)
{
    timer_creat_init();

    xTaskCreate(timer_task, "timer_process", TIMER_TASK_STACK_SIZE, NULL, priority_1, NULL);
}

void timer_creat_init()
{
    long x;
    /* Create then start some timers. Starting the timers before the RTOS scheduler has been
       started means the timers will start running immediately that the RTOS scheduler starts. */
    for( x = 0; x < NUM_TIMERS; x++ )
    {
        xTimers[ x ] = xTimerCreate( /* Just a text name, not used by the RTOS kernel. */
            "Timer",
            /* The timer period in ticks, must be greater than 0. */
            ( 100 * x ) + 100,
            /* The timers will auto-reload themselves when they
               expire. */
            pdTRUE,
            /* The ID is used to store a count of the number of
               times the timer has expired, which is initialized to 0. */
            ( void * ) 0,
            /* Each timer calls the same callback when it expires. */
            vTimerCallback );
        if( xTimers[ x ] == NULL )
        {
            /* The timer was not created. */
        }
        else
        {
            /* Start the timer. No block time is specified, and even if one was it would be
               ignored because the RTOS scheduler has not yet been started. */
            if( xTimerStart( xTimers[ x ], 0 ) != pdPASS )
            {
                /* The timer could not be set into the Active state. */
            }
        }
    }


}


static void timer_task(void *parameter)
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


void vTimerCallback( TimerHandle_t xTimer )
{
    const uint32_t ulMaxExpiryCountBeforeStopping = 10;
    uint32_t ulCount;
    /* The number of times this timer has expired is saved as the timer's ID. Obtain the
       count. */
    ulCount = ( uint32_t ) pvTimerGetTimerID( xTimer );
    /* Increment the count, then test to see if the timer has expired
       ulMaxEx piryCountBeforeStopping yet. */
    ulCount++; 
    /* If the timer has expired 10 times then stop it from running. */
    if( ulCount >= 10 )
    {
        /* Do not use a block time if calling a timer API function from a timer callback
           function, as doing so could cause a deadlock! */
        xTimerStop( xTimer, 0 );
    }
    else
    {
        /* Store the incremented count back into the timer's ID field so it can be read back again
           the next time this software timer expires. */
        vTimerSetTimerID( xTimer, ( void * ) ulCount );
    }
}















