#include "timer.h"

void TIM2_Init(uint16_t ARR,uint16_t PSC) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitSturcture;
	NVIC_InitTypeDef NVIC_InitSturcture;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseInitSturcture.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitSturcture.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_TimeBaseInitSturcture.TIM_Period        = ARR;
	TIM_TimeBaseInitSturcture.TIM_Prescaler     = PSC;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitSturcture);
	
	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	NVIC_InitSturcture.NVIC_IRQChannel                   = TIM2_IRQn;//不需要使能中断
//	NVIC_InitSturcture.NVIC_IRQChannelCmd                = ENABLE;
//	NVIC_InitSturcture.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitSturcture.NVIC_IRQChannelSubPriority        = 0;
	NVIC_Init(&NVIC_InitSturcture);
	
	//TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //不需要使能中断
}
void TIM3_Init(uint16_t ARR,uint16_t PSC) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitSturcture;
	NVIC_InitTypeDef NVIC_InitSturcture;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitSturcture.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitSturcture.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_TimeBaseInitSturcture.TIM_Period        = ARR;
	TIM_TimeBaseInitSturcture.TIM_Prescaler     = PSC;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitSturcture);
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitSturcture.NVIC_IRQChannel                   = TIM3_IRQn;
	NVIC_InitSturcture.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_InitSturcture.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitSturcture.NVIC_IRQChannelSubPriority        = 0;
	NVIC_Init(&NVIC_InitSturcture);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);
}












