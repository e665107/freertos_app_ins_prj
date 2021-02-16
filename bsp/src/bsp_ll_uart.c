#include "bsp_ll_uart.h"

#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

/* static uint8_t aRxBuffer[RXBUFFERSIZE] = {0}; */
void bsp_uart_init()
{
    LL_USART_InitTypeDef USART_InitStruct = {0};
    bsp_uart_gpio_init();
    USARTx_CLK_ENABLE();
    /* USER CODE END USART1_Init 1 */
    USART_InitStruct.BaudRate = 115200;
    USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
    USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    USART_InitStruct.Parity = LL_USART_PARITY_NONE;
    USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init(USART1, &USART_InitStruct);
    LL_USART_ConfigAsyncMode(USART1);
    LL_USART_Enable(USART1);
    /* Enable RXNE and Error interrupts */
    LL_USART_EnableIT_RXNE(USARTx_INSTANCE);
    LL_USART_EnableIT_IDLE(USARTx_INSTANCE);
    /* LL_USART_EnableIT_ERROR(USARTx_INSTANCE); */
    LL_USART_ClearFlag_IDLE(USARTx_INSTANCE);
    NVIC_SetPriority(USARTx_IRQn, 3);
    NVIC_EnableIRQ(USARTx_IRQn);
#if 0
    /* Set clock source */
    /* USARTx_CLK_SOURCE(); */
    /* TX/RX direction */
    LL_USART_SetTransferDirection(USARTx_INSTANCE, LL_USART_DIRECTION_TX_RX);
    LL_USART_SetBaudRate(USARTx_INSTANCE, SystemCoreClock, LL_USART_OVERSAMPLING_16, 115200);
    /* 8 data bit, 1 start bit, 1 stop bit, no parity */
    LL_USART_ConfigCharacter(USARTx_INSTANCE, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);
    /* (5) Enable USART *********************************************************/
    LL_USART_Enable(USARTx_INSTANCE);
    /* Enable RXNE and Error interrupts */
    LL_USART_EnableIT_RXNE(USARTx_INSTANCE);
    LL_USART_EnableIT_IDLE(USARTx_INSTANCE);
    /* LL_USART_EnableIT_ERROR(USARTx_INSTANCE); */
    LL_USART_ClearFlag_IDLE(USARTx_INSTANCE);
    NVIC_SetPriority(USARTx_IRQn, 3);
    NVIC_EnableIRQ(USARTx_IRQn);
#endif
}

void bsp_uart_gpio_init()
{
    USARTx_GPIO_CLK_ENABLE();
    /* Configure Tx Pin as : Alternate function, High Speed, Push pull, Pull up */
    LL_GPIO_SetPinMode(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_MODE_ALTERNATE);
    USARTx_SET_TX_GPIO_AF();
    LL_GPIO_SetPinSpeed(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_PULL_UP);
    /* Configure Rx Pin as : Alternate function, High Speed, Push pull, Pull up */
    LL_GPIO_SetPinMode(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_MODE_ALTERNATE);
    USARTx_SET_RX_GPIO_AF();
    LL_GPIO_SetPinSpeed(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
    /* LL_GPIO_SetPinOutputType(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_OUTPUT_PUSHPULL); */
    LL_GPIO_SetPinPull(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_PULL_UP);
}

void bsp_uart_send_poll(const uint8_t *data, uint16_t data_length)
{
    uint32_t i;

    for (i = 0; i < data_length; i++)
    {
        LL_USART_TransmitData8(USARTx_INSTANCE, *data);
        data++;

        while (!LL_USART_IsActiveFlag_TC(USARTx_INSTANCE))
            ;
    }
}

void Serial_PutString(uint8_t *p_string)
{
    uint16_t length = 0;

    while (p_string[length] != '\0')
        length++;

    bsp_uart_send_poll(p_string, length);
}

void Serial_PutByte( uint8_t param )
{
    LL_USART_TransmitData8(USARTx_INSTANCE, param);

    while (!LL_USART_IsActiveFlag_TC(USARTx_INSTANCE))
        ;
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
    /* HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF); */
    Serial_PutByte(ch);
    return ch;
}

/* void bsp_uart_receive_int(uint8_t *data, uint16_t data_length) */
/* { */
/*     HAL_StatusTypeDef status = HAL_OK; */

/*     LL_USART_ReceiveData8(USARTx_INSTANCE); */

/* } */


