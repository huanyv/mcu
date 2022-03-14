#include "timer.h"

static void BASIC_TIMX_NVIC_Config(void) {
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel                   = BASIC_TIMX_ITCHANNEL;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_Init(&NVIC_InitStructure);
}
void BASIC_TIMX_Cofnig(uint16_t arr,uint16_t psc) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	RCC_APB1PeriphClockCmd(BASIC_TIMX_CLK,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Period        = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler     = psc;
	TIM_TimeBaseInit(BASIC_TIMX,&TIM_TimeBaseInitStructure);
	
	TIM_Cmd(BASIC_TIMX,ENABLE);
	TIM_ITConfig(BASIC_TIMX,TIM_IT_Update,ENABLE);	
	
	BASIC_TIMX_NVIC_Config();	
}


