#include "delay.h"




// 72Mhz   1/8 = 9Mhz   
//每 9 个时钟周期为 1us     
//每 9000 个为 1ms


void delay_us(uint32_t us) {
	uint32_t temp;
	SysTick->LOAD = us * 9; 
	SysTick->VAL = 0x00;
	SysTick->CTRL |= (1<<0);
	do{
		temp = SysTick->CTRL;
	}while( ((temp&(1<<16)) == 0) && (temp&0x01));
	SysTick->VAL = 0x00;
	SysTick->CTRL &= (0<<0);
}

//LODA最大为 2^24  ms最大值不得超过  1864 
void delay_ms(uint16_t ms) {
	uint32_t temp;
	SysTick->LOAD = ms * 9 * 1000;
	SysTick->VAL = 0x00;
	SysTick->CTRL |= (1<<0);
	do{
		temp = SysTick->CTRL;          // 在判断16位的同时，并判断SysTick时钟是否断续使能，务必加入此判断，否则在中断中调用会死机
	}while( ((temp&(1<<16)) == 0) && (temp&0x01)); 
	SysTick->VAL = 0x00;
	SysTick->CTRL &= (0<<0);
}


void delay_s(uint16_t s) {
	while(s--)
		delay_ms(1000);
}






