#include"stm32f10x.h"
#include"wwdg.h"

void WWDG_Init(void) {
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);//使能WWDG时钟
	
	WWDG_SetPrescaler(WWDG_Prescaler_8);//设置预分频参数
	
	WWDG_SetWindowValue(0X5F);//设置上窗口值
		
	WWDG_Enable(0X7F);//使能窗口看门狗
	
	WWDG_ClearFlag();//提前清除标志位（必要）
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel                   = WWDG_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
	NVIC_Init(&NVIC_InitStructure);//初始化中断优先级
	
	WWDG_EnableIT();//使能WWDG中断
}
void WWDG_IRQHandler(void) {//窗口看门狗中断函数

	WWDG_SetCounter(0x7f);//喂狗

	WWDG_ClearFlag();//清除标志位（必要）

	//GPIO_WriteBit(GPIOB,GPIO_Pin_0,(BitAction)!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_0));//如果喂狗成功，灯状态翻转
}

