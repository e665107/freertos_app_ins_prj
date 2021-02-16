#ifndef _BSP_RS485_H
#define _BSP_RS485_H

#include "sys.h"
#include "bsp_hal.h"

extern u8 bsp_rs485_RX_BUF[64];         //���ջ���,���64���ֽ�
extern u8 bsp_rs485_RX_CNT;             //���յ������ݳ���

//����봮���жϽ��գ�����EN_USART2_RXΪ1����������Ϊ0
#define EN_USART2_RX    1           //0,������;1,����.

void bsp_rs485_Init(u32 bound);
void bsp_rs485_Send_Data(u8 *buf,u8 len);
void bsp_rs485_Receive_Data(u8 *buf,u8 *len);   
void bsp_rs485_TX_Set(u8 en);



#endif /* _BSP_485_H */
