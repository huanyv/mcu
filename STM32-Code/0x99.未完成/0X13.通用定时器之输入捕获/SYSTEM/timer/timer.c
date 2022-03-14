#include "timer.h"

void TIM_Cap_Init(uint16_t arr,uint16_t psc) {
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	
	TIM_TimeBaseInitStructure.TIM_Period        = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler     = psc;
	TIM_TimeBaseInitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ICInitStructure.TIM_Channel     = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter    = 0X00;
	TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM2,&TIM_ICInitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update | TIM_IT_CC2,ENABLE);
	
	TIM_Cmd(TIM2,ENABLE);
}	

TIM2_CH2_Capture_Flag_Typedef TIM2_CaptureStructure = {0,0,0,0};

u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值

#if 0 

void TIM2_IRQHandler(void) {
	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == 1) {
		if(TIM2_CaptureStructure.Capture_State == 0) {
			if(TIM2_CaptureStructure.Capture_High_Flag == 1) {
				TIM2_CaptureStructure.Capture_Count++;
				
			}
		}
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
	
	if(TIM_GetITStatus(TIM2,TIM_IT_CC2) == 1) {
		if(TIM2_CaptureStructure.Capture_High_Flag == 0) {
			TIM2_CaptureStructure.Capture_State = 0;
			TIM2_CaptureStructure.Capture_Value = 0;
			TIM2->CNT = 0;
			TIM2_CaptureStructure.Capture_High_Flag = 1;
			TIM_OC2PolarityConfig(TIM2,TIM_OCPolarity_High);
		}
		if(TIM2_CaptureStructure.Capture_High_Flag == 1) {
			TIM2_CaptureStructure.Capture_State = 1;
			TIM2_CaptureStructure.Capture_Value = TIM2->CCR2;
			TIM_OC2PolarityConfig(TIM2,TIM_OCPolarity_Low);
		}
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
	}
	
}

#else
//定时器5中断服务程序	 
void TIM2_IRQHandler(void)
{ 

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)//捕获1发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次上升沿
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM2);
		   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2|TIM_IT_Update); //清除中断标志位
 
}
#endif














