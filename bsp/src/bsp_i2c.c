#include "bsp_i2c.h"
#include "stdio.h"
#include "delay.h"
#include "string.h"

I2C_HandleTypeDef I2cHandle;


void bsp_i2c_init()
{
#ifdef I2C_DMA_ENABLE
    static DMA_HandleTypeDef hdma_tx;
    static DMA_HandleTypeDef hdma_rx;
#endif // DMA_E
    bsp_i2c_gpio_init();
    /*##-1- Configure the I2C peripheral ######################################*/
    /* Put the USART peripheral in the Asynchronous mode (I2C Mode) */
    /* I2C configured as follows:
       - Word Length = 8 Bits (7 data bit + 1 parity bit) : BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
       - Stop Bit    = One Stop bit
       - Parity      = ODD parity
       - BaudRate    = 9600 baud
       - Hardware flow control disabled (RTS and CTS signals) */
    I2cHandle.Instance             = I2Cx;
    I2cHandle.Init.ClockSpeed      = I2C_SPEEDCLOCK;
    I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE;
    I2cHandle.Init.OwnAddress1     = I2C_ADDRESS;
    I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_10BIT;
    I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    I2cHandle.Init.OwnAddress2     = 0xFF;
    I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&I2cHandle) != HAL_OK)
    {
        /* Initialization Error */
        Error_Handler();
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
    /* Associate the initialized DMA handle to the I2C handle */
    __HAL_LINKDMA(&I2cHandle, hdmatx, hdma_tx);
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
    /* Associate the initialized DMA handle to the the I2C handle */
    __HAL_LINKDMA(&I2cHandle, hdmarx, hdma_rx);
    /*##-4- Configure the NVIC for DMA #########################################*/
    /* NVIC configuration for DMA transfer complete interrupt (USART1_TX) */
    HAL_NVIC_SetPriority(USART1_DMA_TX_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(USART1_DMA_TX_IRQn);
    /* NVIC configuration for DMA transfer complete interrupt (USART1_RX) */
    HAL_NVIC_SetPriority(USART1_DMA_RX_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART1_DMA_RX_IRQn);
#endif // MACRO
}

void bsp_i2c_gpio_init()
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* Enable GPIO TX/RX clock */
    I2C_SCL_GPIO_CLK_ENABLE();
    I2C_SDA_GPIO_CLK_ENABLE();
    /* Enable I2C1 clock */
    I2Cx_CLK_ENABLE();
#ifdef I2C1_DMA_ENABLE
    /* Enable DMA clock */
    I2C1_DMA_ENABLE();
#endif // DMA_E
    /*##-2- Configure peripheral GPIO ##########################################*/
    /* I2C SCL GPIO pin configuration  */
    GPIO_InitStruct.Pin       = I2C_SCL_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(I2C_SCL_GPIO_PORT, &GPIO_InitStruct);
    /* I2C SDA GPIO pin configuration  */
    GPIO_InitStruct.Pin = I2C_SDA_PIN;
    HAL_GPIO_Init(I2C_SDA_GPIO_PORT, &GPIO_InitStruct);
}

void bsp_i2c_gpio_deinit()
{
    /*##-1- Reset peripherals ##################################################*/
    I2C_FORCE_RESET();
    I2C_RELEASE_RESET();
    /*##-2- Disable peripherals and GPIO Clocks #################################*/
    /* Configure I2C SCL as alternate function  */
    HAL_GPIO_DeInit(I2C_SCL_GPIO_PORT, I2C_SCL_PIN);
    /* Configure I2C SDA as alternate function  */
    HAL_GPIO_DeInit(I2C_SDA_GPIO_PORT, I2C_SDA_PIN);
}

#ifdef I2C_POLL_ENABLE
void bsp_i2c_send_poll(const char *string)
{
    uint8_t len;
    len = strlen(string);

    if (HAL_I2C_Transmit(&I2cHandle, (uint8_t *)string, len, 0xffff) != HAL_OK)
    {
        /* error_handler(); */
    }
}

void bsp_i2c_receive_poll()
{
    if (HAL_I2C_Receive(&I2cHandle, (uint8_t *)aRxBuffer, RXBUFFERSIZE, 5000) != HAL_OK)
    {
        /* error_handler(); */
    }
    else
    {
        bsp_i2c_send_poll(aRxBuffer);
        clear_buff(aRxBuffer, RXBUFFERSIZE);
    }
}
#endif // MACRO

#ifdef USART1_INT_ENABLE

void bsp_i2c_send_int(const char *string)
{
    uint8_t len;
    len = strlen(string);

    if (HAL_I2C_Transmit_IT(&I2cHandle, (uint8_t *)string, len) != HAL_OK)
        error_handler();

    while (I2cReady != SET)
    {
    }

    /* Reset transmission flag */
    I2cReady = RESET;
}

void bsp_i2c_receive_int()
{
    if (HAL_I2C_Receive_IT(&I2cHandle, (uint8_t *)aRxBuffer, 5) != HAL_OK)
        error_handler();

    /*##-5- Wait for the end of the transfer ###################################*/
    /* while (I2cReady != SET) */
    /* { */
    /* } */
    /* Reset transmission flag */
    /* I2cReady = RESET; */
    /* clear_buff(aRxBuffer, RXBUFFERSIZE); */
}

void bsp_i2c_send_received()
{
    bsp_i2c_send_poll(aRxBuffer);
}

#endif // USART1_INT_ENABLE

/**
 * @brief  UART error callbacks
 * @param  UartHandle: UART handle
 * @note   This example shows a simple way to report transfer error, and you can
 *         add your own implementation.
 * @retval None
 */
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *I2cHandle)
{
    error_handler();
}

#ifdef USART1_DMA_ENABLE
void bsp_i2c_send_dma(const char *string)
{
    uint8_t len;
    len = strlen(string);

    if (HAL_I2C_Transmit_DMA(&I2cHandle, (uint8_t *)string, len) != HAL_OK)
        error_handler();

    while (I2cReady != SET)
    {
    }

    /* Reset transmission flag */
    I2cReady = RESET;
}

void bsp_i2c_receive_dma()
{
    if (HAL_I2C_Receive_DMA(&I2cHandle, (uint8_t *)aRxBuffer, 5) != HAL_OK)
        error_handler();

    /*##-5- Wait for the end of the transfer ###################################*/
    /* while (I2cReady != SET) */
    /* { */
    /* } */
    /* Reset transmission flag */
    /* I2cReady = RESET; */
    /* clear_buff(aRxBuffer, RXBUFFERSIZE); */
}

void USART1_DMA_RX_IRQHandler(void)
{
    HAL_DMA_IRQHandler(I2cHandle.hdmarx);
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
    HAL_DMA_IRQHandler(I2cHandle.hdmatx);
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
    HAL_I2C_IRQHandler(&I2cHandle);
}

/**
 * @brief  Tx Transfer completed callback
 * @param  UartHandle: UART handle.
 * @note   This example shows a simple way to report end of IT Tx transfer, and
 *         you can add your own implementation.
 * @retval None
 */
void HAL_I2C_TxCpltCallback(I2C_HandleTypeDef *I2cHandle)
{
    /* Set transmission flag: transfer complete */
    I2cReady = SET;
}

/**
 * @brief  Rx Transfer completed callback
 * @param  UartHandle: UART handle
 * @note   This example shows a simple way to report end of DMA Rx transfer, and
 *         you can add your own implementation.
 * @retval None
 */
void HAL_I2C_RxCpltCallback(I2C_HandleTypeDef *I2cHandle)
{
    /* Set transmission flag: transfer complete */
    /* I2cReady = SET; */
#ifdef USART1_INT_ENABLE
    bsp_i2c_receive_int();
    bsp_i2c_send_poll(aRxBuffer);
#endif // USART1_INT_ENABLE
#ifdef USART1_DMA_ENABLE
    bsp_i2c_receive_dma();
    bsp_i2c_send_poll(aRxBuffer);
#endif // USART1_DMA_ENABLE
}





