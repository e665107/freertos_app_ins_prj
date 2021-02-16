#ifndef _FREERTOS_FUNC_TEST_H
#define _FREERTOS_FUNC_TEST_H

#include "app_config.h"

#ifdef FREERTOS_TEST_APP

/* #define SEMAPHORE_TEST */

/* #define COUNT_SEMAPHORE_TEST   /\* count events *\/ */

/* #define COUNT_SEMAPHORE_TEST_2  /\* resource management *\/ */

/* #define MUTEX_SEMAPHORE_TEST */

/* #define TASK_NOTIFY_TEST */
#define SOFT_TIMER_TEST

#endif
void freertos_test_task_create(uint8_t priority_1);


#define NO_DELAY 0
#endif /* _FREERTOS_FUNC_TEST_H */













