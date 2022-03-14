#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define     TIMX_GPIO_CLK             RCC_APB2Periph_GPIOA
#define     TIMX_GPIO                 GPIOA
#define     TIMX_PIN                  GPIO_Pin_0

#define     TIMX_PERIPH_CLK           RCC_APB1Periph_TIM5
#define     TIMX                      TIM5
#define     TIMX_CHANNEL              TIM_Channel_1

typedef struct
{
	unsigned Capture_Okay_FLAG:1;
	unsigned Capture_Rising_FLAG:1;
	uint16_t Capture_Value;
	uint16_t Capture_Count;
}Capture_TypeDef;




extern Capture_TypeDef Capture_Structure;



void TIMX_Init(uint16_t arr,uint16_t psc);

#endif /* __TIMER_H */
