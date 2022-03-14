#include "stm32f10x.h"
#include "delay.h"
#include "stdio.h"
#include "usart.h"

void USART1_IRQHandler() {
	uint8_t temp = 0;//接收变量
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == 1) {//检查 USART1 中断发生于于否  发生中断函数值为  1
		temp = USART_ReceiveData(USART1);//数据接收
		USART_SendData(USART1,temp);//数据发送
	}
}

int main(void) {
	My_USART_Init();//自定串口初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断优先组分组   2位抢占  2位响应
	while(1) {
		printf("111111111111111111111\n");
		delay_ms(400);
	}
}





