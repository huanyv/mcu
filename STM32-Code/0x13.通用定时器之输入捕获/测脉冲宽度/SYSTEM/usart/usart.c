#include "usart.h"

static void USARTx_GPIO_Config(void) {
	GPIO_InitTypeDef  GPIO_InitStructure;  //定义IO口初始化结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;   //USART1_TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//GPIO串口发送初始化
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;    //USART1_RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//GPIO串口接收初始化
}
static void USARTx_MODE_Config(void) {
	USART_InitTypeDef  USART_InitStructure;//定义串口初始化结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能串口时钟
	
	USART_InitStructure.USART_BaudRate             = 115200;                             //115200波特率
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;     //无硬件数据流控制
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;      //发送和接收模式都 打开
	USART_InitStructure.USART_Parity               = USART_Parity_No;                    //无奇偶校验位
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;                   //停止位 1
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;                //字长为 8 bit
	USART_Init(USART1,&USART_InitStructure);//串口初始化

#if  USART_ITCONFIG
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//打开中断    接收缓冲区非空   中断
#endif
	
	USART_Cmd(USART1,ENABLE);//使能串口
}

#if  USART_ITCONFIG
static void USARTx_NVIC_Config(void) {
	NVIC_InitTypeDef  NVIC_InitStructure;  //定义中断优先级结构体
	
	NVIC_InitStructure.NVIC_IRQChannel                    = USART1_IRQn;//入口中断通道  stm32f10x.h
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;//使能中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 2;//子优先级
	NVIC_Init(&NVIC_InitStructure);//中断优先级初始化
}
#endif

void USARTx_Init(void) {
	USARTx_GPIO_Config();
	USARTx_MODE_Config();
	
#if  USART_ITCONFIG
	USARTx_NVIC_Config();
#endif	

}



#if    1

#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}

#else

// 需要在魔术棒中选择   Use MicroLIB	  
// 发送数据
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (unsigned char) ch);// USART1 可以换成 USART2 等
	while (!(USART1->SR & USART_FLAG_TXE));
	return (ch);
}
// 接收数据
int GetKey (void)  
{
	while (!(USART1->SR & USART_FLAG_RXNE));
	return ((int)(USART1->DR & 0x1FF));
}




#endif











	






