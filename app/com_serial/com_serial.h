#ifndef __COM_SERIAL_H
#define __COM_SERIAL_H

#include "app_config.h"

void uart_task_create(uint8_t priority_1);
void uart2_task_create(uint8_t priority_1, uint8_t priority_2);

#endif




