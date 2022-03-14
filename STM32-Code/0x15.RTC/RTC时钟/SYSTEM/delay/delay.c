#include "delay.h"


void delay_us(uint32_t us) {
	uint16_t i = 0;
	SysTick_Config(72);//72Mhz的晶振
	for(i = 0; i < us ; i++) {
		while(!(SysTick->CTRL & 0x10000));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;//关闭滴答定时器
}


void delay_ms(uint32_t ms) {
	uint16_t i = 0;
	SysTick_Config(72000);
	for(i = 0; i < ms ; i++) {
		while(!(SysTick->CTRL & 0x10000));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void delay_s(uint16_t s)
{
	while(s--)
		delay_ms(1000);
}





































