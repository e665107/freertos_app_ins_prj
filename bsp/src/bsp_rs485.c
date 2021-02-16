#include "bsp_rs485.h" 
#include "bsp_pcf8574.h"
#include "delay.h"

UART_HandleTypeDef USART2_bsp_rs485Handler;  //USART2���(����bsp_rs485)

#if EN_USART2_RX        //���ʹ���˽���      
//���ջ�����    
u8 bsp_rs485_RX_BUF[64];    //���ջ���,���64���ֽ�.
//���յ������ݳ���
u8 bsp_rs485_RX_CNT=0;  

void USART2_IRQHandler(void)
{
    u8 res;   
    if((__HAL_UART_GET_FLAG(&USART2_bsp_rs485Handler,UART_FLAG_RXNE)!=RESET))  //�����ж�
    {       
        HAL_UART_Receive(&USART2_bsp_rs485Handler,&res,1,1000);
        if(bsp_rs485_RX_CNT<64)
        {
            bsp_rs485_RX_BUF[bsp_rs485_RX_CNT]=res;     //��¼���յ���ֵ
            bsp_rs485_RX_CNT++;                     //������������1 
        } 
    } 
}    
#endif

//��ʼ��IO ����2
//bound:������
void bsp_rs485_Init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_Initure;
    
    bsp_pcf8574_Init();                         //��ʼ��PCF8574�����ڿ���RE��
    
    __HAL_RCC_GPIOA_CLK_ENABLE();           //ʹ��GPIOAʱ��
    __HAL_RCC_USART2_CLK_ENABLE();          //ʹ��USART2ʱ��
    
    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3; //PA2,3
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;      //�����������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    GPIO_Initure.Alternate=GPIO_AF7_USART2; //����ΪUSART2
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);     //��ʼ��PA2,3
    
    //USART ��ʼ������
    USART2_bsp_rs485Handler.Instance=USART2;                    //USART2
    USART2_bsp_rs485Handler.Init.BaudRate=9600;                //������
    USART2_bsp_rs485Handler.Init.WordLength=UART_WORDLENGTH_8B; //�ֳ�Ϊ8λ���ݸ�ʽ
    USART2_bsp_rs485Handler.Init.StopBits=UART_STOPBITS_1;      //һ��ֹͣλ
    USART2_bsp_rs485Handler.Init.Parity=UART_PARITY_NONE;       //����żУ��λ
    USART2_bsp_rs485Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //��Ӳ������
    USART2_bsp_rs485Handler.Init.Mode=UART_MODE_TX_RX;          //�շ�ģʽ
    HAL_UART_Init(&USART2_bsp_rs485Handler);                    //HAL_UART_Init()��ʹ��USART2
    
    __HAL_UART_DISABLE_IT(&USART2_bsp_rs485Handler,UART_IT_TC);
#if EN_USART2_RX
    __HAL_UART_ENABLE_IT(&USART2_bsp_rs485Handler,UART_IT_RXNE);//���������ж�
    HAL_NVIC_EnableIRQ(USART2_IRQn);                        //ʹ��USART1�ж�
    HAL_NVIC_SetPriority(USART2_IRQn,3,3);                  //��ռ���ȼ�3�������ȼ�3
#endif  
    bsp_rs485_TX_Set(0);                                        //����Ϊ����ģʽ    
}

//bsp_rs485����len���ֽ�.
//buf:�������׵�ַ
//len:���͵��ֽ���(Ϊ�˺ͱ�����Ľ���ƥ��,���ｨ�鲻Ҫ����64���ֽ�)
void bsp_rs485_Send_Data(u8 *buf,u8 len)
{
    bsp_rs485_TX_Set(1);            //����Ϊ����ģʽ
    HAL_UART_Transmit(&USART2_bsp_rs485Handler,buf,len,1000);//����2��������
    bsp_rs485_RX_CNT=0;   
    bsp_rs485_TX_Set(0);            //����Ϊ����ģʽ    
}
//bsp_rs485��ѯ���յ�������
//buf:���ջ����׵�ַ
//len:���������ݳ���
void bsp_rs485_Receive_Data(u8 *buf,u8 *len)
{
    u8 rxlen=bsp_rs485_RX_CNT;
    u8 i=0;
    *len=0;             //Ĭ��Ϊ0
    delay_ms(10);       //�ȴ�10ms,��������10msû�н��յ�һ������,����Ϊ���ս���
    if(rxlen==bsp_rs485_RX_CNT&&rxlen)//���յ�������,�ҽ��������
    {
        for(i=0;i<rxlen;i++)
        {
            buf[i]=bsp_rs485_RX_BUF[i]; 
        }       
        *len=bsp_rs485_RX_CNT;  //��¼�������ݳ���
        bsp_rs485_RX_CNT=0;     //����
    }
} 
//bsp_rs485ģʽ����.
//en:0,����;1,����.
void bsp_rs485_TX_Set(u8 en)
{
    bsp_pcf8574_WriteBit(RS485_RE_IO,en);
}
