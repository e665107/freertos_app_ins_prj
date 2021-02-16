#ifndef _BSP_RS485_H
#define _BSP_RS485_H

#include "sys.h"
#include "bsp_hal.h"

extern u8 bsp_rs485_RX_BUF[64];         //接收缓冲,最大64个字节
extern u8 bsp_rs485_RX_CNT;             //接收到的数据长度

//如果想串口中断接收，设置EN_USART2_RX为1，否则设置为0
#define EN_USART2_RX    1           //0,不接收;1,接收.

void bsp_rs485_Init(u32 bound);
void bsp_rs485_Send_Data(u8 *buf,u8 len);
void bsp_rs485_Receive_Data(u8 *buf,u8 *len);   
void bsp_rs485_TX_Set(u8 en);



#endif /* _BSP_485_H */
