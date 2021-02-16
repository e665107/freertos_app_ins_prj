#ifndef _BSP_INIT_H
#define _BSP_INIT_H

#include "app_config.h"


#ifdef SPI_USART_APP
#define BSP_USART2
#define BSP_SPI2
#define BSP_UART
#define BSP_LED
#endif

#ifdef TEST_IO
#define BSP_IO_TEST
#endif // TEST_IO

#ifdef UART2_TEST_APP
#define BSP_UART2
#endif // UART2_TEST_APP

#ifdef UART_TEST_APP
#define BSP_UART
#endif

#ifdef TIM_TEST_APP
#define BSP_TIM
#define BSP_LED
#endif

#ifdef  LED_TEST_APP
#define BSP_LED
#endif

#ifdef I2C_TEST_APP
#define BSP_I2C
#endif // I2C_TEST_APP

#ifdef FREERTOS_TEST_APP
#define BSP_LED
#define BSP_UART
#endif // FREERTOS_TEST_APP

#ifdef CODING_FRAME_APP
/* #define BSP_BUTTON */
#define BSP_UART
#define BSP_485

#endif // 

void bsp_init(void);

#endif /* _BSP_INIT_H */
