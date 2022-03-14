#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f10x.h"

//初始化延迟
//SYSTICK的时钟固定为HCLK时钟的1/8
//SYSCLK:系统时钟

void delay_us(uint32_t us);
void delay_ms(uint16_t ms);
void delay_s(uint16_t s);

#endif





























