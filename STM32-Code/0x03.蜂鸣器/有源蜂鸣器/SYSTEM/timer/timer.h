#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define        BASIC_TIMX                  TIM6
#define        BASIC_TIMX_CLK              RCC_APB1Periph_TIM6
#define        BASIC_TIMX_ITCHANNEL        TIM6_IRQn
#define        BASIC_TIMX_ITFUNCTION       TIM6_IRQHandler



void BASIC_TIMX_Cofnig(uint16_t arr,uint16_t psc);

#endif /* __TIMER_H */
