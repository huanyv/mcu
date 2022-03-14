#include"stm32f10x.h"
#include"key.h"
#include"led.h"
#include"delay.h"


void INT_Init(void) {
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ��ʱ��
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9 | GPIO_PinSource10 | GPIO_PinSource4);//�ж���ӳ��
	
	EXTI_InitStructure.EXTI_Line		= EXTI_Line9 | EXTI_Line10 | EXTI_Line4;//Ҫʹ�ܵ� �ж���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;///ʹ��
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;//�ж�ģʽ
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
	EXTI_Init(&EXTI_InitStructure);//�ⲿ�жϳ�ʼ��
	
	NVIC_InitStructure.NVIC_IRQChannel									 = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd								 = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
	NVIC_Init(&NVIC_InitStructure);//�����ж�9 ���ȼ�
	
	NVIC_InitStructure.NVIC_IRQChannel									 = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd								 = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
	NVIC_Init(&NVIC_InitStructure);//�����ж�10 ���ȼ�
	
	NVIC_InitStructure.NVIC_IRQChannel									 = EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd								 = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
	NVIC_Init(&NVIC_InitStructure);//�����ж�4 ���ȼ�
}

void EXTI9_5_IRQHandler(void) {//�ж� 5-9 ����
	delay_ms(10);
  if(GPIO_ReadInputDataBit(GPIOA,KEY1) == 0) {//�ж�   PA9   �ǲ��� Ϊ �͵�ƽ
		
		GPIO_WriteBit(GPIOB,GPIO_Pin_0,((BitAction)(!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_0))));  //PB0��ת 
		
	}
	EXTI_ClearITPendingBit(EXTI_Line5|EXTI_Line6|EXTI_Line7|EXTI_Line8|EXTI_Line9);//�жϱ�־λ���
}

void EXTI15_10_IRQHandler(void) {
	delay_ms(10);
  if(GPIO_ReadInputDataBit(GPIOA,KEY2) == 0) {
		
		GPIO_WriteBit(GPIOB,GPIO_Pin_1,((BitAction)(!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_1))));   
		
	}
	EXTI_ClearITPendingBit(EXTI_Line10|EXTI_Line11|EXTI_Line12|EXTI_Line13|EXTI_Line14|EXTI_Line15);
}

void EXTI4_IRQHandler(void) {
	delay_ms(10);
  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 0) {
		
		GPIO_WriteBit(GPIOB,GPIO_Pin_1,((BitAction)(!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_1))));   
		
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}

int main(void) {
	Delay_Init();
	LED_Init();
	KEY_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����
	INT_Init();
	while(1) {
		GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		delay_ms(500);
		GPIO_SetBits(GPIOB,GPIO_Pin_7);
		delay_ms(500);
	}
	
}





