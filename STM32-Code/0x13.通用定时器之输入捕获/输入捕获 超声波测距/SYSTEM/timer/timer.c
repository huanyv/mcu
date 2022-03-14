#include "timer.h"

static void TIMX_GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(TIMX_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = TIMX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(TIMX_GPIO,&GPIO_InitStructure);
	TIMX_GPIO->BRR = TIMX_PIN;
}
static void TIMX_MODE_Config(uint16_t arr,uint16_t psc) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	RCC_APB1PeriphClockCmd(TIMX_PERIPH_CLK,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period            = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler         = psc;
	TIM_TimeBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIMX,&TIM_TimeBaseInitStructure);
	
	TIM_ICInitStructure.TIM_Channel     = TIMX_CHANNEL;
	TIM_ICInitStructure.TIM_ICFilter    = 0x00;
	TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIMX,&TIM_ICInitStructure);
	
	TIM_ITConfig(TIMX,TIM_IT_CC1|TIM_IT_Update,ENABLE);
	TIM_Cmd(TIMX,ENABLE);
}
static void TIMX_NVIC_Config(void) {
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIMX_Init(uint16_t arr,uint16_t psc) {
	TIMX_GPIO_Config();
	TIMX_MODE_Config(arr,psc);
	TIMX_NVIC_Config();
}


Capture_TypeDef Capture_Structure = {0,0,0,0};

void TIM5_IRQHandler(void) {
	
	if( TIM_GetITStatus(TIMX,TIM_IT_Update) != RESET ) {
		
		if(Capture_Structure.Capture_Rising_FLAG == 1) // 已成功捕获到上升沿
			if(Capture_Structure.Capture_Okay_FLAG == 0) // 还未捕获OK
				Capture_Structure.Capture_Count++;
		
		TIM_ClearITPendingBit(TIMX,TIM_IT_Update);
	}	
	
	if( TIM_GetITStatus(TIMX,TIM_IT_CC1) != RESET ) {
		
		if(Capture_Structure.Capture_Rising_FLAG == 1) {
			Capture_Structure.Capture_Okay_FLAG  = 1;
			Capture_Structure.Capture_Value = TIMX->CCR1;
			
			TIM_OC1PolarityConfig(TIMX,TIM_OCPolarity_High);
		}
		if(Capture_Structure.Capture_Rising_FLAG == 0) {
			Capture_Structure.Capture_Okay_FLAG   = 0;
			Capture_Structure.Capture_Value       = 0;
			Capture_Structure.Capture_Count       = 0;
			Capture_Structure.Capture_Rising_FLAG = 1;
			TIMX->CCR1 = 0;
			TIMX->CNT  = 0; // 以防计数器溢出 所以要清零
			TIM_OC1PolarityConfig(TIMX,TIM_OCPolarity_Low);
		}
		
		TIM_ClearITPendingBit(TIMX,TIM_IT_CC1);
	}	
}

