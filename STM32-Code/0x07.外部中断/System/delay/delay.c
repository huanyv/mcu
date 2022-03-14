#include "delay.h"




// 72Mhz   1/8 = 9Mhz   
//ÿ 9 ��ʱ������Ϊ 1us     
//ÿ 9000 ��Ϊ 1ms


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

//LODA���Ϊ 2^24  ms���ֵ���ó���  1864 
void delay_ms(uint16_t ms) {
	uint32_t temp;
	SysTick->LOAD = ms * 9 * 1000;
	SysTick->VAL = 0x00;
	SysTick->CTRL |= (1<<0);
	do{
		temp = SysTick->CTRL;          // ���ж�16λ��ͬʱ�����ж�SysTickʱ���Ƿ����ʹ�ܣ���ؼ�����жϣ��������ж��е��û�����
	}while( ((temp&(1<<16)) == 0) && (temp&0x01)); 
	SysTick->VAL = 0x00;
	SysTick->CTRL &= (0<<0);
}


void delay_s(uint16_t s) {
	while(s--)
		delay_ms(1000);
}






