#include "bsp_usart.h"
#include "stdio.h"
#include "delay.h"
#include "string.h"

USART_HandleTypeDef usart_handle;

static uint8_t rx_buffer[RXBUFFERSIZE];

static uint8_t string[] = "hello, world";

void bsp_usart_init()
{
    bsp_usart_gpio_init();
    /*##-1- Configure the USART peripheral ######################################*/
    /* Put the USART peripheral in the synchronous mode (USART Mode) */
    /* USART configured as follows:
       - Word Length = 8 Bits (7 data bit + 1 parity bit) : BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
       - Stop Bit    = One Stop bit
       - Parity      = ODD parity
       - BaudRate    = 9600 baud
       - Hardware flow control disabled (RTS and CTS signals) */
    usart_handle.Instance        = USARTx;
    usart_handle.Init.BaudRate   = 115200;
    usart_handle.Init.WordLength = USART_WORDLENGTH_8B;
    usart_handle.Init.StopBits   = USART_STOPBITS_1;
    usart_handle.Init.Parity     = USART_PARITY_NONE;
    /* usart_handle.Init.HwFlowCtl  = USART_HWCONTROL_NONE; */
    usart_handle.Init.Mode       = USART_MODE_TX_RX;
    usart_handle.Init.CLKPolarity = USART_POLARITY_HIGH;
    usart_handle.Init.CLKPhase   = USART_PHASE_2EDGE;
    usart_handle.Init.CLKLastBit = USART_LASTBIT_ENABLE;

    if (HAL_USART_Init(&usart_handle) != HAL_OK)
    {
        /* Initialization Error */
        /* Error_Handler(); */
    }

    HAL_NVIC_SetPriority(USARTx_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(USARTx_IRQn);
}

void bsp_usart_gpio_init()
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* Enable GPIO TX/RX clock */
    USARTx_TX_GPIO_CLK_ENABLE();
    USARTx_RX_GPIO_CLK_ENABLE();
    /* Enable USARTx clock */
    USARTx_CLK_ENABLE();
    /*##-2- Configure peripheral GPIO ##########################################*/
    /* USART TX GPIO pin configuration  */
    GPIO_InitStruct.Pin       = USARTx_TX_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);
    /* USART RX GPIO pin configuration  */
    GPIO_InitStruct.Pin = USARTx_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
    /* USART CK GPIO pin configuration  */
    GPIO_InitStruct.Pin = USARTx_CK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    HAL_GPIO_Init(USARTx_CK_GPIO_PORT, &GPIO_InitStruct);
}

void bsp_usart_gpio_deinit()
{
    /*##-1- Reset peripherals ##################################################*/
    USARTx_FORCE_RESET();
    USARTx_RELEASE_RESET();
    /*##-2- Disable peripherals and GPIO Clocks #################################*/
    /* Configure USART Tx as alternate function  */
    HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
    /* Configure USART Rx as alternate function  */
    HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);
}

void bsp_usart_send_poll(const char *string)
{
    uint8_t len;
    len = strlen(string);
    HAL_USART_Transmit(&usart_handle, (uint8_t *)string, len, 0xffff);
}

void bsp_usart_receive_int()
{
    if (HAL_USART_Receive_IT(&usart_handle, (uint8_t *)rx_buffer, RXBUFFERSIZE) != HAL_OK)
        printf("rev message is %s", rx_buffer);
}

void USARTx_IRQHandler()
{
    HAL_USART_IRQHandler(&usart_handle);
}







