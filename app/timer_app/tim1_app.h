#ifndef _TIM1_APP_H
#define _TIM1_APP_H

#include "app_config.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

void tim_task_create(uint8_t priority_1);
/* void uart2_task_create(uint8_t priority_1, uint8_t priority_2); */

extern SemaphoreHandle_t b_semaphore;

#endif /* _TIM1_APP_H */




