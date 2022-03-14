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

u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ

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
//��ʱ��5�жϷ������	 
void TIM2_IRQHandler(void)
{ 

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM5CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)//����1���������¼�
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ��������
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM2);
		   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH1_CAPTURE_STA=0;			//���
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);
				TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC2|TIM_IT_Update); //����жϱ�־λ
 
}
#endif














