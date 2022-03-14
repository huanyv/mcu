#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f10x.h"

//初始化延迟
//SYSTICK的时钟固定为HCLK时钟的1/8
//SYSCLK:系统时钟
#define   Delay_Init()       SysTick->CTRL |= 0xFFFFFFFB 	//CTRL寄存器 bit2  选择外部时钟 HCLK/8


void delay_us(uint32_t us);
void delay_ms(uint16_t ms);
void delay_s(uint16_t s);

#endif





























