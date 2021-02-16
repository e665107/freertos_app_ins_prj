#include "bsp_init.h"

#ifdef BSP_LED
#include "bsp_led.h"
#endif // BSP_LED
#ifdef BSP_UART
#include "bsp_uart.h"
#endif // MACRO
#ifdef BSP_USART2
#include "bsp_usart2.h"
#endif // MACRO
#ifdef BSP_SPI2
#include "bsp_spi2.h"
#endif // MACRO
#ifdef BSP_BUTTON
#include "bsp_button.h"
#endif 
#ifdef BSP_PCF8574
#include "bsp_pcf8574.h"
#endif // MACRO

void bsp_init (void)
{
#ifdef BSP_LED
    bsp_led_init(LED0);  /* TEST IO */
#endif // BSP_LED
#ifdef BSP_IO_TEST
    bsp_led_init(LED2);  /* TEST IO */
#endif // BSP_LED
#ifdef BSP_UART
    bsp_uart_init();
#endif
#ifdef BSP_USART2
    bsp_usart2_init();
#endif //
#ifdef BSP_SPI2
     bsp_spi2_init();
#endif // BSP_SPI
#ifdef BSP_UART2
    bsp_uart2_init();
#endif // #define BSP_UART2
#ifdef BSP_TIM
    bsp_tim_init();
#endif // #define BSP_UART2
#ifdef BSP_I2C
    bsp_i2c_init();
#endif // MACRO
#ifdef BSP_BUTTON
    bsp_button_init();
#endif // MACRO
    
#ifdef BSP_PCF8574
#ifndef BSP_485
    bsp_pcf8574_Init();
#endif
#endif // MACRO
    
#ifdef BSP_485
    bsp_rs485_Init();
#endif // MACRO


    
}









