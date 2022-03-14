#include "pwm.h"

void TIM2_ITInit(uint16_t arr,uint16_t psc) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Period        = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler     = psc;
	TIM_TimeBaseInitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM2,ENABLE);
	
}
void TIM2_IRQHandler(void) {
	static uint8_t  value = 0;
	static uint16_t time  = 0;
	static uint8_t  flag  = 0;
	static uint8_t  count = 0;
	count++;time++;
	if(count == 10)count = 0;
	
	if(count < value)
		GPIO_Low8BitWrite(GPIOB,0XFF);
	else
		GPIO_Low8BitWrite(GPIOB,0X00);
	
	if((time>=500)&&(flag == 0)) {
		time = 0;
		value++;
		if(value>9)
			flag = 1;
	}
	if((time>=500)&&(flag == 1)) {
		time = 0;
		value--;
		if(value<1)
			flag = 0;
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}















