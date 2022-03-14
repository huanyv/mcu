#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define       TIMX                      TIM5
#define       TIM_CAPTURE_CHANNL        TIM_Channel_1
#define       TIM_PIN                   GPIO_Pin_0
#define       TIM_GPIO                  GPIOA

typedef struct 
{
	uint16_t Capture_Count;
	uint16_t Capture_Value;
	unsigned Capture_Okay_FLAG:1;
	unsigned Capture_Rising_FLAG:1;
}CAPTURE_TypeDef;




extern CAPTURE_TypeDef CAPTURE_TypeDefStructure;

void TIMx_Init(uint16_t arr,uint16_t psc) ;

#endif /* __TIMER_H */
