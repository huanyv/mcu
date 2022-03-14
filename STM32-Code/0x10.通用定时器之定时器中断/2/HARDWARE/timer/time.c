#include "timer.h"

void TIM2_Init(uint16_t arr,uint16_t psc) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period        = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler     = psc;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel                    = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 2;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM2,ENABLE);
}



