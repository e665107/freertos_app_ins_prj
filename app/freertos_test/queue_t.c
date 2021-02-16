/* freertos */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

/* lib */
#include "common.h"
#include "stdio.h"

/*others  */
#include "semphore_t.h"
#include "bsp_led.h"
#include "freertos_func_test.h"


//LED对应IO初始化
#define TEST7_STACK_SIZE configMINIMAL_STACK_SIZE
#define TEST8_STACK_SIZE configMINIMAL_STACK_SIZE
#define TEST9_STACK_SIZE configMINIMAL_STACK_SIZE


#define SIMPLE_QUEUE_T
/* Define the queue parameters. */

typedef struct a_message
{
    uint8_t uc_message_id;
    uint8_t * uc_data;
} amessage;

#define QUEUE_LENGTH 5 
#define QUEUE_ITEM_SIZE sizeof(amessage)

static void queue_task1( void *pvParameters );
static void queue_task2( void *pvParameters );
static void queue_task3( void *pvParameters );

const TickType_t delay_ms = 1000 / portTICK_PERIOD_MS;

static QueueHandle_t xQueue;

amessage message_to_send;

void queue_t_task_create(uint8_t priority_1, uint8_t priority_2, uint8_t priority_3)
{
    xQueue = xQueueCreate( QUEUE_LENGTH, QUEUE_ITEM_SIZE );

    xTaskCreate(queue_task1, "q_task1", TEST7_STACK_SIZE, NULL, priority_1, (TaskHandle_t)NULL);
    xTaskCreate(queue_task2, "q_task2", TEST8_STACK_SIZE, NULL, priority_2, (TaskHandle_t)NULL);
    xTaskCreate(queue_task3, "q_task3", TEST9_STACK_SIZE, NULL, priority_3, (TaskHandle_t)NULL);
}

static void queue_task1( void *pvParameters )
{
    portBASE_TYPE ret;
    char  string_temp[] = "hello, world";
    message_to_send.uc_data = "hello, world";
    for(;;)
    {
#ifdef SIMPLE_QUEUE_T
        ret = xQueueSend(xQueue, &message_to_send.uc_data, NO_DELAY);
        if(ret == pdPASS)
            printf("queue send success \r\n");
        ret = uxQueueMessagesWaiting(xQueue);
        printf("task1:num of queue items is %d  \r\n", ret);
        xQueueReset(xQueue);  /* empty the queue */
        ret = uxQueueMessagesWaiting(xQueue);
        printf("task1:num of queue items is %d  \r\n", ret);
#endif // SIMPLE_QUEUE_T
        vTaskDelay(delay_ms);
    }
}

static void queue_task2( void *pvParameters )
{
    amessage message_to_recv;
    portBASE_TYPE ret;
    
    for (; ; ) {
#ifdef SIMPLE_QUEUE_T
        xQueueReceive(xQueue, &message_to_recv.uc_data, portMAX_DELAY);
        /* vTaskDelay(delay_ms); */
        printf("queue receive is %s \r\n", message_to_recv.uc_data);
        ret = uxQueueMessagesWaiting(xQueue);
        printf(" task2: num of queue items is %d  \r\n", ret);

#endif // SIMPLE_QUEUE_TMACRO        
        vTaskDelay(delay_ms);
    }
}

static void queue_task3( void *pvParameters )
{
    uint8_t ascii;
    
    message_to_send.uc_message_id = n_to_ascii(5) ;

    for (; ; ) {
        
        printf("message id is %c \r\n", message_to_send.uc_message_id);

        vTaskDelay(delay_ms); 
    }
    
}















 

