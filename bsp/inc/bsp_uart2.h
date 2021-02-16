#ifndef _BSP_UART2_H
#define _BSP_UART2_H

#include "bsp_hal.h"
#include "common.h"

/* Definition for USARTx clock resources */
#define USARTx                           USART2
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART2_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART1_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART1_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_2
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_RX_PIN                    GPIO_PIN_3
#define USARTx_RX_GPIO_PORT              GPIOA


#define USARTx_IRQn                      USART2_IRQn
#define USARTx_IRQHandler                USART2_IRQHandler


/* Definition for USARTx's DMA */

#define USARTx_TX_DMA_CHANNEL             DMA2_Channel4
#define USARTx_RX_DMA_CHANNEL             DMA1_Channel5

/* Definition for USARTx's NVIC */
#define USARTx_DMA_TX_IRQn                DMA1_Channel4_IRQn
#define USARTx_DMA_RX_IRQn                DMA1_Channel5_IRQn
#define USARTx_DMA_TX_IRQHandler          DMA1_Channel4_IRQHandler
#define USARTx_DMA_RX_IRQHandler          DMA1_Channel5_IRQHandler


#define POLL_ENABLE
#define INT_ENABLE
/* #define DMA_ENABLE */

/* #define SEND_INT_ENABLE */
/* #define SEND_POLL_ENABLE */
/* #define RECEIVE_INT_ENABLE */

#define RXBUFFERSIZE                     100

void bsp_uart2_gpio_deinit(void);
void bsp_uart2_gpio_init(void);
void bsp_uart2_init(void);
void bsp_uart2_send_poll(const char *string);
void bsp_uart2_receive_poll(void);
void bsp_uart2_send_int(const char *string);
void bsp_uart2_receive_int(void);

void bsp_uart2_send_received(void);

#endif /* _BSP_UART2_H */


