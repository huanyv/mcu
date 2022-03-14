#ifndef _TIMER_H_
#define _TIMER_H_
#include "sys.h"

void TIM_Cap_Init(uint16_t arr,uint16_t psc);


typedef struct{
	uint16_t Capture_State;//�Ƿ�ɹ�����
	uint16_t Capture_Value;//������
	uint16_t Capture_High_Flag;//���񵽸ߵ�ƽ��־λ
	uint16_t Capture_Count;//���񵽸ߵ�ƽ��־λ
}TIM2_CH2_Capture_Flag_Typedef;

extern TIM2_CH2_Capture_Flag_Typedef TIM2_CaptureStructure;

#endif


