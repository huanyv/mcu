#include "pwm.h"

void TIM3_PWM_Init(uint16_t ARR,uint16_t PSC) {
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);//�򿪶˿ڸ���ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//�򿪶�ʱ��3ʱ��
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);//��ʱ��3PWMͨ��������ӳ��

	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIOB->ODR ^= GPIO_Pin_0;
	
	TIM_TimeBaseInitStructure.TIM_Period        = ARR;//PWM����
	TIM_TimeBaseInitStructure.TIM_Prescaler     = PSC;//Ԥ��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_CounterMode   = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;//ģʽ1 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//ʹ��
	TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_Low;//�͵�ƽ��Ч
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;//��ʱ��3ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;//ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);//ʹ������Ƚ�Ԥװ��
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//�򿪶�ʱ��3�ж�
	
	TIM_Cmd(TIM3,ENABLE);//ʹ��
}

void TIM3_IRQHandler(void) {  //100us�ж�һ��
	static uint16_t ZHOU  = 0;//ռ�ձȣ��ı��ʱ��
	static uint8_t  FLAG  = 0;//�����������𣬻�������
	static uint16_t VALUE = 0;//ռ�ձ�
	ZHOU++;
	if((ZHOU>50)&&(FLAG == 0)) {//��������
		ZHOU = 0;
		VALUE++;//�ı�ռ�ձ�����
		if(VALUE>99)
			FLAG = 1;//�ı䷽��
	}
	
	if((ZHOU>50)&&(FLAG == 1)) {//������
		ZHOU = 0;
		VALUE--;//�ı�ռ�ձȼ�С
		if(VALUE<1)
			FLAG = 0;//�ı䷽��
	}
	
	//GPIO_ReversePin(GPIOB,GPIO_Pin_0);
	
	TIM_SetCompare2(TIM3,VALUE);//�ı�ռ�ձ�
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//����жϱ�־λ
}



