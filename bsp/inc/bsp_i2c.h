#ifndef _BSP_I2C_H
#define _BSP_I2C_H

#include "bsp_hal.h"


#define I2C_CLK_ENABLE()               __HAL_RCC_I2C1_CLK_ENABLE()
#define I2C_SDA_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2C_SCL_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE() 

#define I2C_FORCE_RESET()              __HAL_RCC_I2C1_FORCE_RESET()
#define I2C_RELEASE_RESET()            __HAL_RCC_I2C1_RELEASE_RESET()

/* Definition for I2C Pins */
#define I2C_SCL_PIN                    GPIO_PIN_6
#define I2C_SCL_GPIO_PORT              GPIOB
#define I2C_SDA_PIN                    GPIO_PIN_7
#define I2C_SDA_GPIO_PORT              GPIOB

/* Definition for I2C's NVIC */
#define I2C_EV_IRQn                    I2C1_EV_IRQn
#define I2C_ER_IRQn                    I2C1_ER_IRQn
#define I2C_EV_IRQHandler              I2C1_EV_IRQHandler
#define I2C_ER_IRQHandler              I2C1_ER_IRQHandler

/* Size of Transmission buffer */
#define I2C_TXBUFFERSIZE                      (COUNTOF(aTxBuffer) - 1)
/* Size of Reception buffer */
#define I2C_RXBUFFERSIZE                      TXBUFFERSIZE

#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

#endif /* _BSP_I2C_H */
