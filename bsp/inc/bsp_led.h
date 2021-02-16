#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "bsp_hal.h"

/**
 * @brief LED Types Definition
 */
typedef enum 
{
    LED0 = 0,
    LED1 = 1,
    LED2, 
} led_typedef;

#define LEDn                             3

#define LED0_PIN                         GPIO_PIN_1           /* PB.1 */
#define LED0_GPIO_PORT                   GPIOB
#define LED0_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()  
#define LED0_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()  

#define LED1_PIN                         GPIO_PIN_0           /* PB.0 */
#define LED1_GPIO_PORT                   GPIOB
#define LED1_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()  
#define LED1_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()  


/* TEST IO  BEGIN*/
#define LED2_PIN                         GPIO_PIN_4           /* PA.04 */
#define LED2_GPIO_PORT                   GPIOA
#define LED2_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOA_CLK_ENABLE()  
#define LED2_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOA_CLK_DISABLE()  
/* TEST IO  END*/

#define LEDx_GPIO_CLK_ENABLE(__INDEX__)   do { if((__INDEX__) == 0) LED0_GPIO_CLK_ENABLE(); \
        else if((__INDEX__) == 1) LED1_GPIO_CLK_ENABLE();               \
        else if((__INDEX__) == 2) LED2_GPIO_CLK_ENABLE();} while(0)

void bsp_led_toggle(led_typedef led);
void bsp_led_off(led_typedef led);
void bsp_led_on(led_typedef led);
void bsp_led_init(led_typedef led);


#endif /* _LED_BSP_H */



