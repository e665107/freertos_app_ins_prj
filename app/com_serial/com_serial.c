#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "com_serial.h"
#include "stdio.h" 
#include "freertos_func_test.h"

#include "bsp_uart.h"
#include "bsp_uart2.h"


#define UART_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

#define UART2_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

static void uart_task(void *parameter);

static void uart2_task(void *parameter);

static void uart2_handler_task(void *parameter);

static TickType_t delay_ms = 1000 / portTICK_PERIOD_MS;

SemaphoreHandle_t m_semaphore;

#ifdef UART_TEST_APP
void uart_task_create(uint8_t priority_1)
{
    xTaskCreate(uart_task, "uart_process", UART_TASK_STACK_SIZE, NULL, priority_1, (TaskHandle_t)NULL);
}

static void uart_task(void *parameter)
{
    /* hello */
#ifdef USART1_DMA_ENABLE
    bsp_uart_receive_dma();
#endif
    for(;;) {
#ifdef USART1_DMA_ENABLE
        bsp_uart_send_dma("hello. world \r\n");
#endif
        vTaskDelay(delay_ms);
    }
}

#endif
#ifdef UART2_TEST_APP
void uart2_task_create(uint8_t priority_1, uint8_t priority_2)
{
    xTaskCreate(uart2_task, "uart2_process", UART2_TASK_STACK_SIZE, NULL, priority_1, (TaskHandle_t)NULL);
    xTaskCreate(uart2_handler_task, "uart2_handler_process", UART2_TASK_STACK_SIZE, NULL, priority_2, (TaskHandle_t)NULL);

}

static void uart2_task(void *parameter)
{
    for(;;) {
        
#ifdef INT_ENABLE
        bsp_uart2_send_int("hello,world\r\n");
#elif defined POLL_ENABLE
        bsp_uart2_send_string("hello, world\r\n");
#endif // INT_ENABLE
        
        vTaskDelay(delay_ms);
    }
}

static void uart2_handler_task(void *parameter)
{
#ifdef INT_ENABLE
    bsp_uart2_receive_int();
#endif // INT_ENABLE
     for(;;) {
         
         vTaskDelay(100);
     }
}
#endif // UART2_TEST_APP












