#include "bsp_led.h" 


GPIO_TypeDef* LED_PORT[LEDn] = {LED0_GPIO_PORT,
                                LED1_GPIO_PORT,
                                LED2_GPIO_PORT};

const uint16_t LED_PIN[LEDn] = {LED0_PIN,
                                LED1_PIN,
                                LED2_PIN};

/**
 * @brief  Configures LED GPIO.
 * @param  Led: Specifies the Led to be configured. 
 *   This parameter can be one of following parameters:
 *     @arg LED1
 *     @arg LED2
 *     @arg LED3
 *     @arg LED4
 */
void bsp_led_init(led_typedef led)
{
    GPIO_InitTypeDef  gpioinitstruct = {0};
  
    /* Enable the GPIO_LED clock */
    LEDx_GPIO_CLK_ENABLE(led);

    /* Configure the GPIO_LED pin */
    gpioinitstruct.Pin    = LED_PIN[led];
    gpioinitstruct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpioinitstruct.Pull   = GPIO_NOPULL;
    gpioinitstruct.Speed  = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(LED_PORT[led], &gpioinitstruct);

    HAL_GPIO_WritePin(LED_PORT[led], LED_PIN[led], GPIO_PIN_RESET);
}

/**
 * @brief  Turns selected LED On.
 * @param  Led: Specifies the Led to be set on. 
 *   This parameter can be one of following parameters:
 *     @arg LED1
 *     @arg LED2
 *     @arg LED3
 *     @arg LED4
 */
void bsp_led_on(led_typedef led)
{
    HAL_GPIO_WritePin(LED_PORT[led], LED_PIN[led], GPIO_PIN_SET);
}

/**
 * @brief  Turns selected LED Off.
 * @param  Led: Specifies the Led to be set off. 
 *   This parameter can be one of following parameters:
 *     @arg LED1
 *     @arg LED2
 *     @arg LED3
 *     @arg LED4
 */
void bsp_led_off(led_typedef led)
{
    HAL_GPIO_WritePin(LED_PORT[led], LED_PIN[led], GPIO_PIN_RESET);
}
/**
 * @brief  Toggles the selected LED.
 * @param  Led: Specifies the Led to be toggled. 
 *   This parameter can be one of following parameters:
 *     @arg LED1
 *     @arg LED2
 *     @arg LED3
 *     @arg LED4
 * @retval None
 */
void bsp_led_toggle(led_typedef led)
{
    HAL_GPIO_TogglePin(LED_PORT[led], LED_PIN[led]);
}
