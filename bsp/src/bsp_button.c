#include "bsp_button.h"

static int temp;

/**
 */
#if 0
void bsp_button_init()
{
    GPIO_InitTypeDef  gpioinitstruct = {0};
    /* Enable the GPIO_LED clock */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    /* Configure the GPIO_LED pin */
    gpioinitstruct.Pin    = GPIO_PIN_12 | GPIO_PIN_11 | GPIO_PIN_8;  /* BM1-PIN12 BM2-PIN11 BM3-PIN8*/
    gpioinitstruct.Mode   = GPIO_MODE_INPUT;
    gpioinitstruct.Pull   = GPIO_NOPULL;  /* 外置上拉 */
    gpioinitstruct.Speed  = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &gpioinitstruct);

    /* Enable the GPIO_LED clock */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    /* Configure the GPIO_LED pin */
    /* BM4-PC9 BM5-PIN8 BM6-PIN7 BM7-PIN6 */
    gpioinitstruct.Pin    = GPIO_PIN_9 | GPIO_PIN_8 | GPIO_PIN_7 | GPIO_PIN_6;  
    gpioinitstruct.Mode   = GPIO_MODE_INPUT;
    gpioinitstruct.Pull   = GPIO_NOPULL;  /* 外置上拉 */
    gpioinitstruct.Speed  = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &gpioinitstruct);

    

    
}
#endif


#if 1
void bsp_button_init()
{
    GPIO_InitTypeDef  gpioinitstruct = {0};
    /* Enable the GPIO_LED clock */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    /* Configure the GPIO_LED pin */
    gpioinitstruct.Pin    = GPIO_PIN_0;  /* wake_up */
    gpioinitstruct.Mode   = GPIO_MODE_INPUT;
    gpioinitstruct.Pull   = GPIO_PULLUP;  /*  */
    gpioinitstruct.Speed  = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &gpioinitstruct);
    
    gpioinitstruct.Pin    = GPIO_PIN_3;  /* key0 */
    gpioinitstruct.Mode   = GPIO_MODE_IT_FALLING;
    gpioinitstruct.Pull   = GPIO_PULLUP;  /*  */
    gpioinitstruct.Speed  = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOH, &gpioinitstruct);

    //�ж���3-PH3
    HAL_NVIC_SetPriority(EXTI3_IRQn,4,0);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ2
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);             //ʹ���ж���2
}
#endif

/**
 */
uint8_t bsp_button_in(GPIO_TypeDef* gpio, uint16_t pin)
{
    GPIO_PinState button_s;
    
    button_s = HAL_GPIO_ReadPin(gpio, pin);
    temp = button_s;
    return button_s;
}










