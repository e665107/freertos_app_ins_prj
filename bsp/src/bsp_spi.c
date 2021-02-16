#include "bsp_spi.h"
#include "stdio.h"
#include "delay.h"
#include "string.h"

SPI_HandleTypeDef spi_handle;

static uint8_t rx_buffer[RXBUFFERSIZE] = {0};

static uint8_t string[] = "hello, world";

void bsp_spi_init()
{
    bsp_spi_gpio_init();
    /*##-1- Configure the SPI peripheral ######################################*/
    /* Set the SPI parameters */
    spi_handle.Instance               = SPIx;
    spi_handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    spi_handle.Init.Direction         = SPI_DIRECTION_2LINES;
    spi_handle.Init.CLKPhase          = SPI_PHASE_1EDGE;
    spi_handle.Init.CLKPolarity       = SPI_POLARITY_LOW;
    spi_handle.Init.DataSize          = SPI_DATASIZE_8BIT;
    spi_handle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
    spi_handle.Init.TIMode            = SPI_TIMODE_DISABLE;
    spi_handle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
    spi_handle.Init.CRCPolynomial     = 7;
    spi_handle.Init.NSS               = SPI_NSS_SOFT;
#ifdef MASTER_BOARD
    spi_handle.Init.Mode = SPI_MODE_MASTER;
#else
    spi_handle.Init.Mode = SPI_MODE_SLAVE;
#endif /* MASTER_BOARD */

    if (HAL_SPI_Init(&spi_handle) != HAL_OK)
    {
        /* Initialization Error */
        /* Error_Handler(); */
    }

    /* HAL_NVIC_SetPriority(SPIx_IRQn, 0, 2); */
    /* HAL_NVIC_EnableIRQ(SPIx_IRQn); */
}

void bsp_spi_gpio_init()
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* Enable GPIO TX/RX clock */
    SPIx_SCK_GPIO_CLK_ENABLE();
    SPIx_MISO_GPIO_CLK_ENABLE();
    SPIx_MOSI_GPIO_CLK_ENABLE();
    /* Enable SPI clock */
    SPIx_CLK_ENABLE();
    /*##-2- Configure peripheral GPIO ##########################################*/
    /* SPI SCK GPIO pin configuration  */
    GPIO_InitStruct.Pin       = SPIx_SCK_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);
    /* SPI MISO GPIO pin configuration  */
    GPIO_InitStruct.Pin = SPIx_MISO_PIN;
    HAL_GPIO_Init(SPIx_MISO_GPIO_PORT, &GPIO_InitStruct);
    /* SPI MOSI GPIO pin configuration  */
    GPIO_InitStruct.Pin = SPIx_MOSI_PIN;
    HAL_GPIO_Init(SPIx_MOSI_GPIO_PORT, &GPIO_InitStruct);
}

void bsp_spi_gpio_deinit()
{
    /* Configure SPI SCK as alternate function  */
    HAL_GPIO_DeInit(SPIx_SCK_GPIO_PORT, SPIx_SCK_PIN);
    /* Configure SPI MISO as alternate function  */
    HAL_GPIO_DeInit(SPIx_MISO_GPIO_PORT, SPIx_MISO_PIN);
    /* Configure SPI MOSI as alternate function  */
    HAL_GPIO_DeInit(SPIx_MOSI_GPIO_PORT, SPIx_MOSI_PIN);
}

void bsp_spi_send_poll(const char *string)
{
    uint8_t len;
    len = strlen(string);
    HAL_SPI_Transmit(&spi_handle, (uint8_t *)string, len, 0xffff);
}

bool bsp_spi_receive_poll()
{
    if (HAL_SPI_Receive(&spi_handle, (uint8_t *)rx_buffer, RXBUFFERSIZE, 0) == HAL_OK)
    {
        printf("rev message is %s", rx_buffer);
        return SUCCESS;
    }

    else
        return ERROR;
}

void bsp_spi_receive_int()
{
    if (HAL_SPI_Receive_IT(&spi_handle, (uint8_t *)rx_buffer, RXBUFFERSIZE) != HAL_OK)
    {
        printf("rev message is %s", rx_buffer);
        clear_buff(rx_buffer, RXBUFFERSIZE);
    }
}

void SPIx_IRQHandler()
{
    HAL_SPI_IRQHandler(&spi_handle);
}








