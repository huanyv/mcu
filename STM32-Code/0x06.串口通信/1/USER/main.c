#include"stm32f10x.h"
#include"delay.h"

void User_USART_Init() {
	GPIO_InitTypeDef   GPIO_InitStructure;  //定义IO口初始化结构体
	USART_InitTypeDef  USART_InitStructure;//定义串口初始化结构体
	NVIC_InitTypeDef   NVIC_InitStructure;  //定义中断优先级结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能时钟
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;   //USART1_TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//GPIO串口发送初始化
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;    //USART1_RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//GPIO串口接收初始化
	
	USART_InitStructure.USART_BaudRate             = 115200;                             //115200波特率
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;     //无硬件数据流控制
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;      //发送和接收模式都 打开
	USART_InitStructure.USART_Parity               = USART_Parity_No;                    //无奇偶校验位
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;                   //停止位 1
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;                //字长为 8 bit
	USART_Init(USART1,&USART_InitStructure);//串口初始化
	
	NVIC_InitStructure.NVIC_IRQChannel                    = USART1_IRQn;//入口中断通道  stm32f10x.h
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;//使能中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;//子优先级
	NVIC_Init(&NVIC_InitStructure);//中断优先级初始化
	
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//打开中断    接收缓冲区非空   中断
	
	USART_Cmd(USART1,ENABLE);//使能串口
}

void USART1_IRQHandler() {
	uint8_t temp = 0;//接收变量
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == 1) {//检查 USART1 中断发生于于否  发生中断函数值为  1
		temp = USART_ReceiveData(USART1);//数据接收
		USART_SendData(USART1,temp);//数据发送
	}
}

int main(void) {
	User_USART_Init();//自定串口初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断优先组分组   2位抢占  2位响应
	while(1);
}





