#ifndef _BSP_SPI_H
#define _BSP_SPI_H

#include "bsp_hal.h"
#include "common.h"

/* Definition for SPIx clock resources */
#define SPIx                             SPI2
#define SPIx_CLK_ENABLE()                __HAL_RCC_SPI2_CLK_ENABLE()
#define DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define SPIx_SCK_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_MISO_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define SPIx_MOSI_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

/* Definition for SPIx Pins */
#define SPIx_SCK_PIN                     GPIO_PIN_13
#define SPIx_SCK_GPIO_PORT               GPIOB
#define SPIx_MISO_PIN                    GPIO_PIN_14
#define SPIx_MISO_GPIO_PORT              GPIOB
#define SPIx_MOSI_PIN                    GPIO_PIN_15
#define SPIx_MOSI_GPIO_PORT              GPIOB

/* Definition for SPIx's DMA */
#define SPIx_TX_DMA_CHANNEL              DMA1_Channel5
#define SPIx_RX_DMA_CHANNEL              DMA1_Channel4


/* Definition for SPIx's NVIC */
#define SPIx_DMA_TX_IRQn                 DMA1_Channel5_IRQn
#define SPIx_DMA_RX_IRQn                 DMA1_Channel4_IRQn
#define SPIx_DMA_TX_IRQHandler           DMA1_Channel5_IRQHandler
#define SPIx_DMA_RX_IRQHandler           DMA1_Channel4_IRQHandler
#define SPIx_IRQHandler                  SPI2_IRQHandler

#define SPIx_IRQn                        SPI2_IRQn

/* Size of buffer */
#define BUFFERSIZE                       (COUNTOF(aTxBuffer) - 1)

/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

#define RXBUFFERSIZE 100
/* Exported functions ------------------------------------------------------- */
/* #define MASTER_BOARD */

void SPIx_IRQHandler(void);

void bsp_spi_receive_int(void);

void bsp_spi_send_poll(const char *string);

bool bsp_spi_receive_poll(void);

void bsp_spi_gpio_deinit(void);

void bsp_spi_gpio_init(void);

void bsp_spi_init(void);

#endif /* _BSP_SPI_H */
