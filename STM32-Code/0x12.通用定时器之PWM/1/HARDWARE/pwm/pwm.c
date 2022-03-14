#include "pwm.h"

void TIM3_PWM_Init(uint16_t ARR,uint16_t PSC) {
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);//打开端口复用时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//打开定时器3时钟
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);//定时器3PWM通道部分重映射

	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIOB->ODR ^= GPIO_Pin_0;
	
	TIM_TimeBaseInitStructure.TIM_Period        = ARR;//PWM周期
	TIM_TimeBaseInitStructure.TIM_Prescaler     = PSC;//预分频值
	TIM_TimeBaseInitStructure.TIM_CounterMode   = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;//模式1 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//使能
	TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_Low;//低电平有效
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;//定时器3通道
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;//使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);//使能输出比较预装载
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//打开定时器3中断
	
	TIM_Cmd(TIM3,ENABLE);//使能
}

void TIM3_IRQHandler(void) {  //100us中断一次
	static uint16_t ZHOU  = 0;//占空比，改变的时间
	static uint8_t  FLAG  = 0;//方向，由亮到灭，或，由灭到亮
	static uint16_t VALUE = 0;//占空比
	ZHOU++;
	if((ZHOU>50)&&(FLAG == 0)) {//由亮到灭
		ZHOU = 0;
		VALUE++;//改变占空比增加
		if(VALUE>99)
			FLAG = 1;//改变方向
	}
	
	if((ZHOU>50)&&(FLAG == 1)) {//由灭到亮
		ZHOU = 0;
		VALUE--;//改变占空比减小
		if(VALUE<1)
			FLAG = 0;//改变方向
	}
	
	//GPIO_ReversePin(GPIOB,GPIO_Pin_0);
	
	TIM_SetCompare2(TIM3,VALUE);//改变占空比
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//清除中断标志位
}



