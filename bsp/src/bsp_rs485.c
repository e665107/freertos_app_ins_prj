#include "bsp_rs485.h" 
#include "bsp_pcf8574.h"
#include "delay.h"

UART_HandleTypeDef USART2_bsp_rs485Handler;  //USART2句柄(用于bsp_rs485)

#if EN_USART2_RX        //如果使能了接收      
//接收缓存区    
u8 bsp_rs485_RX_BUF[64];    //接收缓冲,最大64个字节.
//接收到的数据长度
u8 bsp_rs485_RX_CNT=0;  

void USART2_IRQHandler(void)
{
    u8 res;   
    if((__HAL_UART_GET_FLAG(&USART2_bsp_rs485Handler,UART_FLAG_RXNE)!=RESET))  //接收中断
    {       
        HAL_UART_Receive(&USART2_bsp_rs485Handler,&res,1,1000);
        if(bsp_rs485_RX_CNT<64)
        {
            bsp_rs485_RX_BUF[bsp_rs485_RX_CNT]=res;     //记录接收到的值
            bsp_rs485_RX_CNT++;                     //接收数据增加1 
        } 
    } 
}    
#endif

//初始化IO 串口2
//bound:波特率
void bsp_rs485_Init(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_Initure;
    
    bsp_pcf8574_Init();                         //初始化PCF8574，用于控制RE脚
    
    __HAL_RCC_GPIOA_CLK_ENABLE();           //使能GPIOA时钟
    __HAL_RCC_USART2_CLK_ENABLE();          //使能USART2时钟
    
    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3; //PA2,3
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;      //复用推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    GPIO_Initure.Alternate=GPIO_AF7_USART2; //复用为USART2
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);     //初始化PA2,3
    
    //USART 初始化设置
    USART2_bsp_rs485Handler.Instance=USART2;                    //USART2
    USART2_bsp_rs485Handler.Init.BaudRate=9600;                //波特率
    USART2_bsp_rs485Handler.Init.WordLength=UART_WORDLENGTH_8B; //字长为8位数据格式
    USART2_bsp_rs485Handler.Init.StopBits=UART_STOPBITS_1;      //一个停止位
    USART2_bsp_rs485Handler.Init.Parity=UART_PARITY_NONE;       //无奇偶校验位
    USART2_bsp_rs485Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //无硬件流控
    USART2_bsp_rs485Handler.Init.Mode=UART_MODE_TX_RX;          //收发模式
    HAL_UART_Init(&USART2_bsp_rs485Handler);                    //HAL_UART_Init()会使能USART2
    
    __HAL_UART_DISABLE_IT(&USART2_bsp_rs485Handler,UART_IT_TC);
#if EN_USART2_RX
    __HAL_UART_ENABLE_IT(&USART2_bsp_rs485Handler,UART_IT_RXNE);//开启接收中断
    HAL_NVIC_EnableIRQ(USART2_IRQn);                        //使能USART1中断
    HAL_NVIC_SetPriority(USART2_IRQn,3,3);                  //抢占优先级3，子优先级3
#endif  
    bsp_rs485_TX_Set(0);                                        //设置为接收模式    
}

//bsp_rs485发送len个字节.
//buf:发送区首地址
//len:发送的字节数(为了和本代码的接收匹配,这里建议不要超过64个字节)
void bsp_rs485_Send_Data(u8 *buf,u8 len)
{
    bsp_rs485_TX_Set(1);            //设置为发送模式
    HAL_UART_Transmit(&USART2_bsp_rs485Handler,buf,len,1000);//串口2发送数据
    bsp_rs485_RX_CNT=0;   
    bsp_rs485_TX_Set(0);            //设置为接收模式    
}
//bsp_rs485查询接收到的数据
//buf:接收缓存首地址
//len:读到的数据长度
void bsp_rs485_Receive_Data(u8 *buf,u8 *len)
{
    u8 rxlen=bsp_rs485_RX_CNT;
    u8 i=0;
    *len=0;             //默认为0
    delay_ms(10);       //等待10ms,连续超过10ms没有接收到一个数据,则认为接收结束
    if(rxlen==bsp_rs485_RX_CNT&&rxlen)//接收到了数据,且接收完成了
    {
        for(i=0;i<rxlen;i++)
        {
            buf[i]=bsp_rs485_RX_BUF[i]; 
        }       
        *len=bsp_rs485_RX_CNT;  //记录本次数据长度
        bsp_rs485_RX_CNT=0;     //清零
    }
} 
//bsp_rs485模式控制.
//en:0,接收;1,发送.
void bsp_rs485_TX_Set(u8 en)
{
    bsp_pcf8574_WriteBit(RS485_RE_IO,en);
}
