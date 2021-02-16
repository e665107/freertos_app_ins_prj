#ifndef __LED_FLASH_H
#define __LED_FLASH_H
/* kernel include */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"
#include "bsp_led.h"

////////////////////////////////////////////////////////////////////////////////////    

void vStartLED0FlashTasks(portBASE_TYPE priority);
void vStartLED1FlashTasks(portBASE_TYPE priority);
void vStartLED2FlashTasks(portBASE_TYPE priority);

#endif





