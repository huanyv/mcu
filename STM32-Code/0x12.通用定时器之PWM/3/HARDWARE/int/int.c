#include "int.h"
#include "delay.h"

void INT_Init(void) {
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	EXTI_InitStructure.EXTI_Line     = EXTI_Line9;
	EXTI_InitStructure.EXTI_LineCmd  = ENABLE;
	EXTI_InitStructure.EXTI_Mode     = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger  = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel									 = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd								 = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
	NVIC_Init(&NVIC_InitStructure);//配置中断9 优先级	
	
}
void EXTI9_5_IRQHandler(void) {//中断 5-9 函数
	static uint16_t  value = 10;
	delay_ms(10);
  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9) == 0) {//判断   PA9   是不是 为 低电平
			value = value+30;
			TIM_SetCompare2(TIM3,value);
			if(value>=100)value = 10;
	}
	EXTI_ClearITPendingBit(EXTI_Line9);//中断标志位清除
}

