/* os */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* lib */
#include "stdio.h"
#include "common.h"

/* app */
#include "task_t.h"
#include "semphore_t.h"
#include "queue_t.h"
/* bsp */

/* func */
#include "freertos_func_test.h"


void freertos_test_task_create(uint8_t priority_1)
{
#ifdef TASK_NOTIFY_TEST
    task_t_task_create(priority_1);
#elif defined SEMAPHORE_TEST
    semphore_t_task_create(priority_1+1,  priority_1,  priority_1);
#elif defined SOFT_TIMER_TEST
    timer_task_create(priority_1);
#endif
    /* xTaskCreate(app_name_task, "app_name_process", app_name_TASK_STACK_SIZE, NULL, priority_1, (TaskHandle_t)NULL); */

}




















