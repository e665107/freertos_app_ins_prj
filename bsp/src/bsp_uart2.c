#include "bsp_uart2.h"
#include "stdio.h"
#include "delay.h"
#include "string.h"

#ifdef USE_RTOS
#include "FreeRTOS.h"
#include "semphr.h"
#endif // USE_RTOS

UART_HandleTypeDef Uart2Handle;

#ifdef INT_ENABLE
__IO ITStatus UartReady = RESET;
#endif // INT_ENABLE

static uint8_t aRxBuffer[RXBUFFERSIZE];

uint8_t string[] = "hello, world";

void bsp_uart2_init()
{
#ifdef DMA_ENABLEMACRO
    static DMA_HandleTypeDef hdma_tx;
    static DMA_HandleTypeDef hdma_rx;
#endif // DMA_ENABLEMACRO
    bsp_uart2_gpio_init();
    /*##-1- Configure the UART2 peripheral ######################################*/
    /* Put the USART peripheral in the Asynchronous mode (UART2 Mode) */
    /* UART2 configured as follows:
       - Word Length = 8 Bits (7 data bit + 1 parity bit) : BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
       - Stop Bit    = One Stop bit
       - Parity      = ODD parity
       - BaudRate    = 9600 baud
       - Hardware flow control disabled (RTS and CTS signals) */
    Uart2Handle.Instance        = USARTx;
    Uart2Handle.Init.BaudRate   = 9600;
    Uart2Handle.Init.WordLength = UART_WORDLENGTH_8B;
    Uart2Handle.Init.StopBits   = UART_STOPBITS_1;
    Uart2Handle.Init.Parity     = UART_PARITY_NONE;
    Uart2Handle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    Uart2Handle.Init.Mode       = UART_MODE_TX_RX;

    if (HAL_UART_Init(&Uart2Handle) != HAL_OK)
    {
        /* Initialization Error */
        /* Error_Handler(); */
    }

#ifdef INT_ENABLE
    HAL_NVIC_SetPriority(USARTx_IRQn, 0, 4);
    HAL_NVIC_EnableIRQ(USARTx_IRQn);
#endif
#ifdef DMA_ENABLE
    /*##-3- Configure the DMA ##################################################*/
    /* Configure the DMA handler for Transmission process */
    hdma_tx.Instance                 = USARTx_TX_DMA_CHANNEL;
    hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
    hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;
    hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    hdma_tx.Init.Mode                = DMA_NORMAL;
    hdma_tx.Init.Priority            = DMA_PRIORITY_LOW;
    HAL_DMA_Init(&hdma_tx);
    /* Associate the initialized DMA handle to the UART handle */
    __HAL_LINKDMA(huart, hdmatx, hdma_tx);
    /* Configure the DMA handler for reception process */
    hdma_rx.Instance                 = USARTx_RX_DMA_CHANNEL;
    hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
    hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;
    hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    hdma_rx.Init.Mode                = DMA_NORMAL;
    hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;
    HAL_DMA_Init(&hdma_rx);
    /* Associate the initialized DMA handle to the the UART handle */
    __HAL_LINKDMA(huart, hdmarx, hdma_rx);
#endif // DMA_ENABLE
}

void bsp_uart2_gpio_init()
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* Enable GPIO TX/RX clock */
    USARTx_TX_GPIO_CLK_ENABLE();
    USARTx_RX_GPIO_CLK_ENABLE();
    /* Enable USARTx clock */
    USARTx_CLK_ENABLE();
    /*##-2- Configure peripheral GPIO ##########################################*/
    /* UART2 TX GPIO pin configuration  */
    GPIO_InitStruct.Pin       = USARTx_TX_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);
    /* UART2 RX GPIO pin configuration  */
    GPIO_InitStruct.Pin = USARTx_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
}

void bsp_uart2_gpio_deinit()
{
    /*##-1- Reset peripherals ##################################################*/
    USARTx_FORCE_RESET();
    USARTx_RELEASE_RESET();
    /*##-2- Disable peripherals and GPIO Clocks #################################*/
    /* Configure UART2 Tx as alternate function  */
    HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
    /* Configure UART2 Rx as alternate function  */
    HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);
}

#ifdef POLL_ENABLE
void bsp_uart2_send_poll(const char *string)
{
    uint8_t len;
    len = strlen(string);

    if (HAL_UART_Transmit(&Uart2Handle, (uint8_t *)string, len, 0xffff) != HAL_OK)
    {
        /* error_handler(); */
    }
}

void bsp_uart2_receive_poll()
{
    if (HAL_UART_Receive(&Uart2Handle, (uint8_t *)aRxBuffer, RXBUFFERSIZE, 5000) != HAL_OK)
    {
        /* error_handler(); */
    }
    else
    {
        bsp_uart2_send_string(aRxBuffer);
        clear_buff(aRxBuffer, RXBUFFERSIZE);
    }
}
#endif // MACRO

#ifdef INT_ENABLE

void bsp_uart2_send_int(const char *string)
{
    uint8_t len;
    len = strlen(string);

    if (HAL_UART_Transmit_IT(&Uart2Handle, (uint8_t *)string, len) != HAL_OK)
        error_handler();

    while (UartReady != SET)
    {
    }

    /* Reset transmission flag */
    UartReady = RESET;
}

void bsp_uart2_receive_int()
{
    if (HAL_UART_Receive_IT(&Uart2Handle, (uint8_t *)aRxBuffer, 5) != HAL_OK)
        error_handler();

    /*##-5- Wait for the end of the transfer ###################################*/
    /* while (UartReady != SET) */
    /* { */
    /* } */
    /* Reset transmission flag */
    /* UartReady = RESET; */
    /* clear_buff(aRxBuffer, RXBUFFERSIZE); */
}

void bsp_uart2_send_received()
{
    bsp_uart2_send_poll(aRxBuffer);
}

void USARTx_IRQHandler()
{
    HAL_UART_IRQHandler(&Uart2Handle);
}

/**
 * @brief  Tx Transfer completed callback
 * @param  UartHandle: UART handle.
 * @note   This example shows a simple way to report end of IT Tx transfer, and
 *         you can add your own implementation.
 * @retval None
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    /* Set transmission flag: transfer complete */
    UartReady = SET;
}

/**
 * @brief  Rx Transfer completed callback
 * @param  UartHandle: UART handle
 * @note   This example shows a simple way to report end of DMA Rx transfer, and
 *         you can add your own implementation.
 * @retval None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    /* Set transmission flag: transfer complete */
    /* UartReady = SET; */
    bsp_uart2_receive_int();
    bsp_uart2_send_poll(aRxBuffer);
}

#endif // INT_ENABLE

/**
 * @brief  UART error callbacks
 * @param  UartHandle: UART handle
 * @note   This example shows a simple way to report transfer error, and you can
 *         add your own implementation.
 * @retval None
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
    error_handler();
}







