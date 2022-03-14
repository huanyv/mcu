#include "stm32f10x.h"
#include "delay.h"
#include "stdio.h"
#include "usart.h"

void USART1_IRQHandler() {
	uint8_t temp = 0;//���ձ���
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == 1) {//��� USART1 �жϷ������ڷ�  �����жϺ���ֵΪ  1
		temp = USART_ReceiveData(USART1);//���ݽ���
		USART_SendData(USART1,temp);//���ݷ���
	}
}

int main(void) {
	My_USART_Init();//�Զ����ڳ�ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�ж����������   2λ��ռ  2λ��Ӧ
	while(1) {
		printf("111111111111111111111\n");
		delay_ms(400);
	}
}





