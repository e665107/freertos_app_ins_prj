#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "semphore_t.h"
#include "stdio.h" 
#include "bsp_led.h"
#include "freertos_func_test.h"

//LED对应IO初始化
#define TEST1_STACK_SIZE configMINIMAL_STACK_SIZE
#define TEST2_STACK_SIZE configMINIMAL_STACK_SIZE
#define TEST3_STACK_SIZE configMINIMAL_STACK_SIZE

static void sempore_task1( void *pvParameters );
static void sempore_task2( void *pvParameters );
static void sempore_task3( void *pvParameters );

static SemaphoreHandle_t b_semaphore;
static SemaphoreHandle_t c_semaphore;
static SemaphoreHandle_t m_semaphore;


const TickType_t delay_ms = 1000 / portTICK_PERIOD_MS;
static uint32_t m_cnt = 0;  /* m_cnt */
static uint32_t a = 0;
void semphore_t_task_create(uint8_t priority_1, uint8_t priority_2, uint8_t priority_3)
{
#ifdef SEMAPHORE_TEST
    b_semaphore = xSemaphoreCreateBinary();
#endif
     
#ifdef COUNT_SEMAPHORE_TEST 
    c_semaphore = xSemaphoreCreateCounting( 10, 0 );
#endif // COUNT_SEMAPHORE_TEST
#ifdef COUNT_SEMAPHORE_TEST_2
    c_semaphore = xSemaphoreCreateCounting( 10, 10 );
    a = 0;
#endif // COUNT_SEMAPHORE_TEST
#ifdef MUTEX_SEMAPHORE_TEST
    m_semaphore = xSemaphoreCreateMutex();
    configASSERT(m_semaphore);
#endif // MUTEX_SEMAPHORE_TEST
    xTaskCreate(sempore_task1, "s_task1", TEST1_STACK_SIZE, NULL, priority_1, (TaskHandle_t)NULL);
    xTaskCreate(sempore_task2, "s_task2", TEST2_STACK_SIZE, NULL, priority_2, (TaskHandle_t)NULL);
    xTaskCreate(sempore_task3, "s_task3", TEST3_STACK_SIZE, NULL, priority_3, (TaskHandle_t)NULL);

}

static void sempore_task1( void *pvParameters )
{
    uint8_t semphr_cnt;
    
    for(;;)
    {
#ifdef COUNT_SEMAPHORE_TEST
        printf("sempore_1 is working \r\n");
        xSemaphoreGive(c_semaphore);
        semphr_cnt = uxSemaphoreGetCount(c_semaphore);
        printf("sempore_counts  is %d \r\n", semphr_cnt);
#endif // COUNT_SEMAPHORE_TEST

#ifdef SEMAPHORE_TEST
        printf("sempore_1 is working \r\n");
        xSemaphoreGive(b_semaphore);
#endif // SEMAPHORE_TEST

#ifdef COUNT_SEMAPHORE_TEST_2
        xSemaphoreTake(c_semaphore, portMAX_DELAY);
        a++;
        semphr_cnt = uxSemaphoreGetCount(c_semaphore);
        printf("sempore_counts  is %d \r\n", semphr_cnt);
        if(a > 9)
        {
            a = 0;
            xSemaphoreGive(c_semaphore);


        }
#endif // COUNT_SEMAPHORE_TEST_2

#ifdef MUTEX_SEMAPHORE_TEST
        xSemaphoreTake(m_semaphore, portMAX_DELAY);       
        m_cnt++;
        xSemaphoreGive(m_semaphore);
#endif // MUTEX_SEMAPHORE_TEST
        vTaskDelay(delay_ms);
    }
}

static void sempore_task2( void *pvParameters )
{
    for (; ; ) {
        
#ifdef SEMAPHORE_TEST
        xSemaphoreTake(b_semaphore, portMAX_DELAY);
        printf("sempore_2 is working \r\n");
#endif // MACRO
        
#ifdef COUNT_SEMAPHORE_TEST
        xSemaphoreTake(c_semaphore, portMAX_DELAY);
        printf("sempore_2 is working \r\n");
#endif // COUNT_SEMAPHORE_TEST
        vTaskDelay(delay_ms);
    }
}

static void sempore_task3( void *pvParameters )
{
    uint32_t heap_remain;
    for (; ; ) {
        
        printf("sempore_3 is working \r\n");
        heap_remain = xPortGetMinimumEverFreeHeapSize();
        printf("heap remain  is %d \r\n", heap_remain);
        
        vTaskDelay(delay_ms); 
    }
    
}















