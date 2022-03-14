#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define       TIM_COUNT             1000
#define       THx                   (65536-TIM_COUNT)/256
#define       TLx                   (65536-TIM_COUNT)%256

sbit motor = P1^4;




void TIM_Init(void);
void PWM_SPEED();

#endif /* __TIMER_H */




