#include "FreeRTOS.h"
#include "task.h"
#include "app_init.h"


#ifdef LED_APP
#include "led_flash.h"
#endif
#ifdef FREERTOS_TEST_APP
#include "freertos_func_test.h"
#endif
#ifdef COM_SERIAL_APP
#include "com_serial.h"
#endif
#ifdef USART_SPI_COMMUNICATE_APP
#include "usart_spi_com.h"
#endif
#ifdef CODING_FRAME_APP
#include "coding_frame_creat.h"
#endif

void app_init(void)
{ 
#ifdef TEST_IO
    vStartLED2FlashTasks( TEST1_TASK_PRIORITY );
#endif // TEST_IO
#ifdef SPI_USART_APP
    usart_spi_task_create(TEST4_TASK_PRIORITY, TEST2_TASK_PRIORITY);
#endif
#ifdef UART2_TEST_APP
    uart2_task_create(TEST1_TASK_PRIORITY, TEST2_TASK_PRIORITY);
#endif // UART2_TEST_APP
#ifdef UART_TEST_APP
    uart_task_create(TEST1_TASK_PRIORITY);
#endif // UART_TEST_APP
#ifdef TIM_TEST_APP
    tim_task_create(TEST3_TASK_PRIORITY);
#endif // TIM_TEST_APP
#ifdef LED_TEST_APP
    vStartLED0FlashTasks( TEST2_TASK_PRIORITY );
#endif // TIM_TEST_APP

#ifdef I2C_TEST_APP
#endif // 

#ifdef FREERTOS_TEST_APP
    freertos_test_task_create(TEST2_TASK_PRIORITY);
#endif // FREERTOS_TEST_APP
#ifdef CODING_FRAME_APP
    coding_frame_task_create();
#endif // FREERTOS_TEST_APP
}





