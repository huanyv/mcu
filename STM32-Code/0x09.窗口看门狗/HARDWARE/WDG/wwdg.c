#include"stm32f10x.h"
#include"wwdg.h"

void WWDG_Init(void) {
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);//ʹ��WWDGʱ��
	
	WWDG_SetPrescaler(WWDG_Prescaler_8);//����Ԥ��Ƶ����
	
	WWDG_SetWindowValue(0X5F);//�����ϴ���ֵ
		
	WWDG_Enable(0X7F);//ʹ�ܴ��ڿ��Ź�
	
	WWDG_ClearFlag();//��ǰ�����־λ����Ҫ��
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel                   = WWDG_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
	NVIC_Init(&NVIC_InitStructure);//��ʼ���ж����ȼ�
	
	WWDG_EnableIT();//ʹ��WWDG�ж�
}
void WWDG_IRQHandler(void) {//���ڿ��Ź��жϺ���

	WWDG_SetCounter(0x7f);//ι��

	WWDG_ClearFlag();//�����־λ����Ҫ��

	//GPIO_WriteBit(GPIOB,GPIO_Pin_0,(BitAction)!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_0));//���ι���ɹ�����״̬��ת
}

