#ifndef _BSP_LL_UART_H
#define _BSP_LL_UART_H

#include "bsp_ll.h"
#include "stm32f4xx_ll_usart.h"

/* USART1 instance is used. (TX on PA.09, RX on PA.10)
   (requires wiring USART1 TX/Rx Pins to USB to UART adapter) */
#define USARTx_INSTANCE               USART1
#define USARTx_CLK_ENABLE()           LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)
#define USARTx_CLK_SOURCE()           LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK1)
#define USARTx_IRQn                   USART1_IRQn
#define USARTx_IRQHandler             USART1_IRQHandler
#define USARTx_GPIO_CLK_ENABLE()      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)   /* Enable the peripheral clock of GPIOA */
#define USARTx_TX_PIN                 LL_GPIO_PIN_9
#define USARTx_TX_GPIO_PORT           GPIOA
#define USARTx_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_9, LL_GPIO_AF_7)
#define USARTx_RX_PIN                 LL_GPIO_PIN_10
#define USARTx_RX_GPIO_PORT           GPIOA
#define USARTx_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_10, LL_GPIO_AF_7)


void USART_CharReception_Callback(void);
void USARTx_IRQHandler(void);
void bsp_uart_gpio_init(void);

void bsp_uart_init(void);
void bsp_uart_receive_int(const uint8_t *data, uint16_t data_length);

void bsp_uart_send_poll(const uint8_t *data, uint16_t data_length);
void Serial_PutString(uint8_t *p_string);
void Serial_PutByte( uint8_t param );
uint8_t Serial_GetByte(void);



#endif /* _BSP_LL_UART_H */
