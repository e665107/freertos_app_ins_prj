#include "bsp_uart.h"
#include "stdio.h"
#include "delay.h"
#include "string.h"

#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

UART_HandleTypeDef UartHandle;

#if defined (USART1_INT_ENABLE) || defined (USART1_DMA_ENABLE)
__IO ITStatus UartReady = RESET;
#endif // USART1_INT_ENABLE

uint8_t aRxBuffer[RXBUFFERSIZE];

uint8_t string[] = "hello, world";

void bsp_uart_init()
{
#ifdef USART1_DMA_ENABLE
    static DMA_HandleTypeDef hdma_tx;
    static DMA_HandleTypeDef hdma_rx;
#endif // DMA_E
    bsp_uart_gpio_init();
    /*##-1- Configure the UART peripheral ######################################*/
    /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
    /* UART configured as follows:
       - Word Length = 8 Bits (7 data bit + 1 parity bit) : BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
       - Stop Bit    = One Stop bit
       - Parity      = ODD parity
       - BaudRate    = 9600 baud
       - Hardware flow control disabled (RTS and CTS signals) */
    UartHandle.Instance        = USART1;
    UartHandle.Init.BaudRate   = 9600;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits   = UART_STOPBITS_1;
    UartHandle.Init.Parity     = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode       = UART_MODE_TX_RX;

    if (HAL_UART_Init(&UartHandle) != HAL_OK)
    {
        /* Initialization Error */
        /* Error_Handler(); */
    }

#if defined  (USART1_INT_ENABLE) || defined (USART1_DMA_ENABLE)
    HAL_NVIC_SetPriority(USART1_IRQn, 1, 2);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
#endif // USART1_INT_ENABLE    
#ifdef USART1_DMA_ENABLE
    /*##-3- Configure the DMA ##################################################*/
    /* Configure the DMA handler for Transmission process */
    hdma_tx.Instance                 = USART1_TX_DMA_CHANNEL;
    hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
    hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;
    hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    hdma_tx.Init.Mode                = DMA_NORMAL;
    hdma_tx.Init.Priority            = DMA_PRIORITY_LOW;
    HAL_DMA_Init(&hdma_tx);
    /* Associate the initialized DMA handle to the UART handle */
    __HAL_LINKDMA(&UartHandle, hdmatx, hdma_tx);
    /* Configure the DMA handler for reception process */
    hdma_rx.Instance                 = USART1_RX_DMA_CHANNEL;
    hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
    hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;
    hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
    hdma_rx.Init.Mode                = DMA_NORMAL;
    hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;
    HAL_DMA_Init(&hdma_rx);
    /* Associate the initialized DMA handle to the the UART handle */
    __HAL_LINKDMA(&UartHandle, hdmarx, hdma_rx);
    /*##-4- Configure the NVIC for DMA #########################################*/
    /* NVIC configuration for DMA transfer complete interrupt (USART1_TX) */
    HAL_NVIC_SetPriority(USART1_DMA_TX_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(USART1_DMA_TX_IRQn);
    /* NVIC configuration for DMA transfer complete interrupt (USART1_RX) */
    HAL_NVIC_SetPriority(USART1_DMA_RX_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART1_DMA_RX_IRQn);
#endif // MACRO
}

void bsp_uart_gpio_init()
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* Enable GPIO TX/RX clock */
    USART1_TX_GPIO_CLK_ENABLE();
    USART1_RX_GPIO_CLK_ENABLE();
    /* Enable USART1 clock */
    USART1_CLK_ENABLE();
#ifdef USART1_DMA_ENABLE
    /* Enable DMA clock */
    USART1_DMA1_CLK_ENABLE();
#endif // DMA_E
    /*##-2- Configure peripheral GPIO ##########################################*/
    /* UART TX GPIO pin configuration  */
    GPIO_InitStruct.Pin       = USART1_TX_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStruct);
    /* UART RX GPIO pin configuration  */
    GPIO_InitStruct.Pin = USART1_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStruct);
}

void bsp_uart_gpio_deinit()
{
    /*##-1- Reset peripherals ##################################################*/
    USART1_FORCE_RESET();
    USART1_RELEASE_RESET();
    /*##-2- Disable peripherals and GPIO Clocks #################################*/
    /* Configure UART Tx as alternate function  */
    HAL_GPIO_DeInit(USART1_TX_GPIO_PORT, USART1_TX_PIN);
    /* Configure UART Rx as alternate function  */
    HAL_GPIO_DeInit(USART1_RX_GPIO_PORT, USART1_RX_PIN);
}

/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART1 and Loop until the end of transmission */
    HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);

    return ch;
}

#ifdef USART1_POLL_ENABLE
void bsp_uart_send_poll(const char *string)
{
    uint8_t len;
    len = strlen(string);

    if (HAL_UART_Transmit(&UartHandle, (uint8_t *)string, len, 0xffff) != HAL_OK)
    {
        /* error_handler(); */
    }
}

void bsp_uart_receive_poll()
{
    if (HAL_UART_Receive(&UartHandle, (uint8_t *)aRxBuffer, RXBUFFERSIZE, 5000) != HAL_OK)
    {
        /* error_handler(); */
    }
    else
    {
        bsp_uart_send_poll(aRxBuffer);
        clear_buff(aRxBuffer, RXBUFFERSIZE);
    }
}
#endif // MACRO

#ifdef USART1_INT_ENABLE

void bsp_uart_send_int(const char *string)
{
    uint8_t len;
    len = strlen(string);

    if (HAL_UART_Transmit_IT(&UartHandle, (uint8_t *)string, len) != HAL_OK)
        error_handler();

    while (UartReady != SET)
    {
    }

    /* Reset transmission flag */
    UartReady = RESET;
}

void bsp_uart_receive_int()
{
    if (HAL_UART_Receive_IT(&UartHandle, (uint8_t *)aRxBuffer, 5) != HAL_OK)
        error_handler();

    /*##-5- Wait for the end of the transfer ###################################*/
    /* while (UartReady != SET) */
    /* { */
    /* } */
    /* Reset transmission flag */
    /* UartReady = RESET; */
    /* clear_buff(aRxBuffer, RXBUFFERSIZE); */
}

void bsp_uart_send_received()
{
    bsp_uart_send_poll(aRxBuffer);
}

#endif // USART1_INT_ENABLE

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

#ifdef USART1_DMA_ENABLE
void bsp_uart_send_dma(const char *string)
{
    uint8_t len;
    len = strlen(string);

    if (HAL_UART_Transmit_DMA(&UartHandle, (uint8_t *)string, len) != HAL_OK)
        error_handler();

    while (UartReady != SET)
    {
    }

    /* Reset transmission flag */
    UartReady = RESET;
}
void bsp_uart_receive_dma()
{
    if (HAL_UART_Receive_DMA(&UartHandle, (uint8_t *)aRxBuffer, 5) != HAL_OK)
        error_handler();

    /*##-5- Wait for the end of the transfer ###################################*/
    /* while (UartReady != SET) */
    /* { */
    /* } */
    /* Reset transmission flag */
    /* UartReady = RESET; */
    /* clear_buff(aRxBuffer, RXBUFFERSIZE); */
}
void USART1_DMA_RX_IRQHandler(void)
{
    HAL_DMA_IRQHandler(UartHandle.hdmarx);
}
/**
 * @brief  This function handles DMA interrupt request.
 * @param  None
 * @retval None
 * @Note   This function is redefined in "main.h" and related to DMA
 *         used for USART data reception
 */
void USART1_DMA_TX_IRQHandler(void)
{
    HAL_DMA_IRQHandler(UartHandle.hdmatx);
}
#endif

/**
 * @brief  This function handles UART interrupt request.
 * @param  None
 * @retval None
 * @Note   This function is redefined in "main.h" and related to DMA
 *         used for USART data transmission
 */
void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&UartHandle);
}

#if defined (USART1_DMA_ENABLE)
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
#ifdef USART1_INT_ENABLE
    bsp_uart_receive_int();
    bsp_uart_send_poll(aRxBuffer);
#endif // USART1_INT_ENABLE
#ifdef USART1_DMA_ENABLE
    bsp_uart_receive_dma();
    bsp_uart_send_poll(aRxBuffer);
#endif // USART1_DMA_ENABLE
}
#endif



