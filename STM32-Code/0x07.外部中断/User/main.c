#include"stm32f10x.h"
#include"key.h"
#include"led.h"
#include"delay.h"


void INT_Init(void) {
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能时钟
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9 | GPIO_PinSource10 | GPIO_PinSource4);//中断线映射
	
	EXTI_InitStructure.EXTI_Line		= EXTI_Line9 | EXTI_Line10 | EXTI_Line4;//要使能的 中断线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;///使能
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	EXTI_Init(&EXTI_InitStructure);//外部中断初始化
	
	NVIC_InitStructure.NVIC_IRQChannel									 = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd								 = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
	NVIC_Init(&NVIC_InitStructure);//配置中断9 优先级
	
	NVIC_InitStructure.NVIC_IRQChannel									 = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd								 = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
	NVIC_Init(&NVIC_InitStructure);//配置中断10 优先级
	
	NVIC_InitStructure.NVIC_IRQChannel									 = EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd								 = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
	NVIC_Init(&NVIC_InitStructure);//配置中断4 优先级
}

void EXTI9_5_IRQHandler(void) {//中断 5-9 函数
	delay_ms(10);
  if(GPIO_ReadInputDataBit(GPIOA,KEY1) == 0) {//判断   PA9   是不是 为 低电平
		
		GPIO_WriteBit(GPIOB,GPIO_Pin_0,((BitAction)(!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_0))));  //PB0翻转 
		
	}
	EXTI_ClearITPendingBit(EXTI_Line5|EXTI_Line6|EXTI_Line7|EXTI_Line8|EXTI_Line9);//中断标志位清除
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置中断优先级分组
	INT_Init();
	while(1) {
		GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		delay_ms(500);
		GPIO_SetBits(GPIOB,GPIO_Pin_7);
		delay_ms(500);
	}
	
}





