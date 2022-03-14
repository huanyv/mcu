#include "usart.h"

static void USARTx_GPIO_Config(void) {
	GPIO_InitTypeDef  GPIO_InitStructure;  //定义IO口初始化结构体
	
	RCC_APB2PeriphClockCmd(USARTX_GPIO_CLK ,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin   = USARTX_TX_PIN;   //USART1_TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USARTX_GPIO,&GPIO_InitStructure);//GPIO串口发送初始化
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_InitStructure.GPIO_Pin   = USARTX_RX_PIN;    //USART1_RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USARTX_GPIO,&GPIO_InitStructure);//GPIO串口接收初始化
}
static void USARTx_MODE_Config(void) {
	USART_InitTypeDef  USART_InitStructure;//定义串口初始化结构体

	USARTX_PERIPH_APBx_CLK_CMD(USARTX_PERIPH_CLK,ENABLE);//使能串口时钟

	USART_InitStructure.USART_BaudRate             = USARTX_BAUD;                             //115200波特率
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;     //无硬件数据流控制
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;      //发送和接收模式都 打开
	USART_InitStructure.USART_Parity               = USART_Parity_No;                    //无奇偶校验位
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;                   //停止位 1
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;                //字长为 8 bit
	USART_Init(USARTX,&USART_InitStructure);//串口初始化

#if  USART_IT_EN
	USART_ITConfig(USARTX,USARTX_IT_CONFIG,ENABLE);//打开中断    接收缓冲区非空   中断
#endif

	USART_Cmd(USARTX,ENABLE);//使能串口
}

#if  USART_IT_EN
static void USARTx_NVIC_Config(void) {
	NVIC_InitTypeDef  NVIC_InitStructure;  //定义中断优先级结构体
	
	NVIC_InitStructure.NVIC_IRQChannel                    = USARTX_IT_CHANNL;//入口中断通道  stm32f10x.h
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;//使能中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 2;//子优先级
	NVIC_Init(&NVIC_InitStructure);//中断优先级初始化
}
#endif

void USARTx_Init(void) {
	USARTx_GPIO_Config();
	USARTx_MODE_Config();
	
#if  USART_IT_EN
	USARTx_NVIC_Config();
#endif

}

#if  USART_IT_EN
void USARTX_IT_FUNCTION(void) {
	uint8_t temp;
	if( USART_GetITStatus(USARTX,USARTX_IT_CONFIG) != RESET ) {
		
		temp = USART_ReceiveData(USARTX);
		USART_SendData(USARTX,temp+1);
		
		USART_ClearITPendingBit(USARTX,USARTX_IT_CONFIG);
	}
	
}
#endif


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
	while((USARTX->SR&0X40)==0);//循环发送,直到发送完毕   
    USARTX->DR = (u8) ch;      
	return ch;
}

#else

// 需要在魔术棒中选择   Use MicroLIB	  
// 发送数据
int fputc(int ch, FILE *f)
{
	USART_SendData(USARTX, (unsigned char) ch);// USART1 可以换成 USART2 等
	while (!(USARTX->SR & USART_FLAG_TXE));
	return (ch);
}
// 接收数据
int GetKey (void)  
{
	while (!(USARTX->SR & USART_FLAG_RXNE));
	return ((int)(USARTX->DR & 0x1FF));
}




#endif











	






