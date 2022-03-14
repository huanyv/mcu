#include "timer.h"
#include "stm32f10x.h"

void TIM2_Init(uint16_t arr,uint16_t psc) {
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitSructure;//��ʱ����ʼ���ṹ��
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ��ʱ��
	
	TIM_TimeBaseInitSructure.TIM_ClockDivision     = TIM_CKD_DIV1;//
	TIM_TimeBaseInitSructure.TIM_CounterMode       = TIM_CounterMode_Up;//���ϼ������ģʽ
	TIM_TimeBaseInitSructure.TIM_Period            = arr;//����ֵʱ��
	TIM_TimeBaseInitSructure.TIM_Prescaler         = psc;//Ԥ��Ƶϵ��
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitSructure);//��ʼ����ʱ��
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//ʹ�ܶ�ʱ���ж�
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�ж����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
	NVIC_Init(&NVIC_InitStructure);   
	
	TIM_Cmd(TIM2,ENABLE);//ʹ�ܶ�ʱ�� 
	
}

void TIM2_IRQHandler(void) {//��ʱ���жϺ���

	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == 1) {//����Ƕ�ʱ��2�������ж� 
		
		
		GPIO_WriteBit(GPIOB,GPIO_Pin_0,(BitAction)!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_0));
		GPIO_WriteBit(GPIOB,GPIO_Pin_1,(BitAction)!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_1));
		GPIO_WriteBit(GPIOB,GPIO_Pin_2,(BitAction)!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_2));
		GPIO_WriteBit(GPIOB,GPIO_Pin_3,(BitAction)!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_3));
		GPIO_WriteBit(GPIOB,GPIO_Pin_4,(BitAction)!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_4));
		GPIO_WriteBit(GPIOB,GPIO_Pin_5,(BitAction)!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5));
		GPIO_WriteBit(GPIOB,GPIO_Pin_6,(BitAction)!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_6));
		GPIO_WriteBit(GPIOB,GPIO_Pin_7,(BitAction)!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_7));
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//��� �ж� ��־λ
	}
}


















