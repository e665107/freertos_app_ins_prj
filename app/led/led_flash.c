#include "led_flash.h" 
#include "bsp_led.h" 
#include "stdio.h" 
/*  */
//LED对应IO初始化
#define LED0_STACK_SIZE configMINIMAL_STACK_SIZE
#define LED1_STACK_SIZE configMINIMAL_STACK_SIZE
#define LED2_STACK_SIZE configMINIMAL_STACK_SIZE


static void vTask_LED0( void *pvParameters );
static void vTask_LED1( void *pvParameters );
static void vTask_LED2( void *pvParameters );


const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

void vStartLED0FlashTasks(portBASE_TYPE priority)
{

    xTaskCreate(vTask_LED0, "led0", LED0_STACK_SIZE, NULL, priority, (TaskHandle_t)NULL);

}

void vStartLED1FlashTasks(portBASE_TYPE priority)
{

    xTaskCreate(vTask_LED1, "led1", LED1_STACK_SIZE, NULL, priority, (TaskHandle_t)NULL);
    
}

void vStartLED2FlashTasks(portBASE_TYPE priority)
{

    xTaskCreate(vTask_LED2, "led2", LED2_STACK_SIZE, NULL, priority, (TaskHandle_t)NULL);
    
}

static void vTask_LED0( void *pvParameters )
{
    for(;;)
    {
        /* printf(" led0 is flashing \r\n"); */
        bsp_led_toggle(LED0);
        vTaskDelay(xDelay);
    }
    
}

static void vTask_LED1( void *pvParameters )
{

    
    for (; ; ) {
        /* printf(" led1 is flashing \r\n"); */
        vTaskDelay(xDelay);
    }
    
}

static void vTask_LED2( void *pvParameters )
{

    for (; ; ) {
        /* printf(" led2 is flashing \r\n"); */
        bsp_led_toggle(LED2);

        vTaskDelay(xDelay);  
    }
    
}















