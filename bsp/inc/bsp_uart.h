#ifndef _BSP_UART_H
#define _BSP_UART_H


#include "bsp_hal.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor USARTx/UARTx instance used and associated
   resources */

/* Definition for USARTx clock resources */
#define USART1_CLK_ENABLE()              __HAL_RCC_USART1_CLK_ENABLE();
#define USART1_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USART1_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define USART1_FORCE_RESET()             __HAL_RCC_USART1_FORCE_RESET()
#define USART1_RELEASE_RESET()           __HAL_RCC_USART1_RELEASE_RESET()

/* Definition for USART1 Pins */
#define USART1_TX_PIN                    GPIO_PIN_9
#define USART1_TX_GPIO_PORT              GPIOA
#define USART1_RX_PIN                    GPIO_PIN_10
#define USART1_RX_GPIO_PORT              GPIOA
#define RXBUFFERSIZE                     100  

/* DMA */
#define USART1_DMA1_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
/* Definition for USART1's DMA */
#define USART1_TX_DMA_CHANNEL             DMA1_Channel4
#define USART1_RX_DMA_CHANNEL             DMA1_Channel5


/* Definition for USART1's NVIC */
#define USART1_DMA_TX_IRQn                DMA1_Channel4_IRQn
#define USART1_DMA_RX_IRQn                DMA1_Channel5_IRQn
#define USART1_DMA_TX_IRQHandler          DMA1_Channel4_IRQHandler
#define USART1_DMA_RX_IRQHandler          DMA1_Channel5_IRQHandler

#define USART1_POLL_ENABLE
/* #define USART1_INT_ENABLE */
/* #define USART1_DMA_ENABLE */

/* #define USART1_SEND_INT_ENABLE */
/* #define USART1_SEND_POLL_ENABLE */
/* #define USART1_RECEIVE_INT_ENABLE */


void bsp_uart_gpio_deinit(void);
void bsp_uart_gpio_init(void);
void bsp_uart_init(void);
void bsp_uart_send_poll(const char *string);
void bsp_uart_receive_poll(void);
void bsp_uart_send_int(const char *string);
void bsp_uart_receive_int(void);

void bsp_uart_send_received(void);

void bsp_uart_receive_dma(void);
void bsp_uart_send_dma(const char *string);



#endif /* _BSP_UART_H */ 
