/* os */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "app_init.h"

/* lib */
#include "stdio.h"
#include "common.h"

/* app */
#include "button_process.h"
#include "hsm_ins_process.h"

/* #include "semphore_t.h" */
/* #include "queue_t.h" */
/* bsp */

/* func */
#include "coding_frame_creat.h"

void coding_frame_task_create()
{
#ifdef BUTTON_PROCESS
    button_task_create(TEST1_TASK_PRIORITY);
#endif
#ifdef USB_OTG_PROCESS

#endif
#ifdef USB_STORAGE_PROCESS

#endif
#ifdef USB_COMMUNICATION_PROCESS

#endif
#ifdef UART_ZIGBEE_PROCESS

#endif 
#ifdef UART_WIFI_PROCESS

#endif
#ifdef UART_MODUBUS_PROCESS

#endif
#ifdef UART_BLUTOOTH_PROCESS

#endif
#ifdef UART_485_PROCESS
    uart_485_process_task_create(TEST1_TASK_PRIORITY);
#endif
#ifdef TFT_DISPLAY_PROCESS

#endif
#ifdef TEMPRATURE_PROCESS

#endif
#ifdef SD_CARD_FAT_PROCESS

#endif
#ifdef SOUND_PROCESS

#endif

#ifdef HSM_PROCESS
    hsm_ins_process_task_create(TEST1_TASK_PRIORITY);
#endif


#ifdef TIMER_PERIOID_PROCESS


#endif // MACRO
}




















 
