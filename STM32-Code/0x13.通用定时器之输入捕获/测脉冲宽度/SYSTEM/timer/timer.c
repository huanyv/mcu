#include "timer.h"
#include "key.h"


static void TIMx_MODE_Config(uint16_t arr,uint16_t psc) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_Period        = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler     = psc;
	TIM_TimeBaseInit(TIMX,&TIM_TimeBaseInitStructure);
	
	TIM_ICInitStructure.TIM_Channel     = TIM_CAPTURE_CHANNL;
	TIM_ICInitStructure.TIM_ICFilter    = 0x00;
	TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIMX,&TIM_ICInitStructure);
	
	TIM_ITConfig(TIMX,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	TIM_Cmd(TIMX,ENABLE);
}
static void TIMx_NVIC_Config(void) {
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void TIMx_Init(uint16_t arr,uint16_t psc) {
	KEY_GPIO_Config();
	TIMx_MODE_Config(arr,psc);
	TIMx_NVIC_Config();
}




CAPTURE_TypeDef CAPTURE_TypeDefStructure = {0,0,0,0};

void TIM5_IRQHandler(void) {
	
	if( TIM_GetITStatus(TIMX,TIM_IT_Update) != RESET ) {
   
		if( CAPTURE_TypeDefStructure.Capture_Rising_FLAG == 1 )
			if( CAPTURE_TypeDefStructure.Capture_Okay_FLAG == 0 )
				CAPTURE_TypeDefStructure.Capture_Count++;
		
		TIM_ClearITPendingBit(TIMX,TIM_IT_Update);
	}
	
	
	if( TIM_GetITStatus(TIMX,TIM_IT_CC1) != RESET ) {
		
		if( CAPTURE_TypeDefStructure.Capture_Rising_FLAG == 1 ) {
			CAPTURE_TypeDefStructure.Capture_Okay_FLAG  = 1;
			CAPTURE_TypeDefStructure.Capture_Value = TIMX->CCR1;
			
			TIM_OC1PolarityConfig(TIMX,TIM_ICPolarity_Rising);
		}
		
		if( CAPTURE_TypeDefStructure.Capture_Rising_FLAG == 0 ) {
			CAPTURE_TypeDefStructure.Capture_Count  = 0;
			CAPTURE_TypeDefStructure.Capture_Value  = 0;
			CAPTURE_TypeDefStructure.Capture_Okay_FLAG  = 0;
			CAPTURE_TypeDefStructure.Capture_Rising_FLAG = 1;
			TIMX->CCR1 = 0;
			TIMX->CNT = 0;
			TIM_OC1PolarityConfig(TIMX,TIM_ICPolarity_Falling);
		}
		
		TIM_ClearITPendingBit(TIMX,TIM_IT_CC1);
	}
	
}












