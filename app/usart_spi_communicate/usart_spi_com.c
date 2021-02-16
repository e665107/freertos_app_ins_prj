#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "com_serial.h"
#include "stdio.h" 
#include "freertos_func_test.h"

#include "bsp_usart2.h"
#include "bsp_spi2.h"

static char string[] = "hello, world";

/*IO 口连线
 *PA4->PB13(CK-SCK) PA2->PB15(TX-MOSI) PA3->PB14(RX-MISO)
 *
 */
#define USART_TASK_STACK_SIZE configMINIMAL_STACK_SIZE
#define SPI_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

static void usart_task(void *parameter);
static void spi_task(void *parameter);

static TickType_t delay_ms = 1000 / portTICK_PERIOD_MS;

void usart_spi_task_create(uint8_t priority_1, uint8_t priority_2)
{
    xTaskCreate(usart_task, "usart_process", USART_TASK_STACK_SIZE, NULL, priority_1, (TaskHandle_t)NULL);
    xTaskCreate(spi_task, "spi_process", SPI_TASK_STACK_SIZE, NULL, priority_2, (TaskHandle_t)NULL);
}

static void usart_task(void *parameter)
{

    for(;;) {
        bsp_usart_send_poll(string);
        vTaskDelay(delay_ms);
    }
}

static void spi_task(void *parameter)
{
    for(;;) {
        bsp_spi_receive_poll();
        vTaskDelay(delay_ms);
    }
}













