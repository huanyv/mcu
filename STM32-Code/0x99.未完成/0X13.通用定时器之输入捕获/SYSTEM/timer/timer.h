#ifndef _TIMER_H_
#define _TIMER_H_
#include "sys.h"

void TIM_Cap_Init(uint16_t arr,uint16_t psc);


typedef struct{
	uint16_t Capture_State;//是否成功捕获
	uint16_t Capture_Value;//脉宽长度
	uint16_t Capture_High_Flag;//捕获到高电平标志位
	uint16_t Capture_Count;//捕获到高电平标志位
}TIM2_CH2_Capture_Flag_Typedef;

extern TIM2_CH2_Capture_Flag_Typedef TIM2_CaptureStructure;

#endif


