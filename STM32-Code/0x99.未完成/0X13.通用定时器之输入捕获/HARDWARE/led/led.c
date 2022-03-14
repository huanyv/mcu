#include"led.h"
#include"stm32f10x.h"

void LED_init(void)
{
	GPIO_InitTypeDef GPIOinit;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIOinit.GPIO_Pin=LED;
	GPIOinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIOinit.GPIO_Mode=GPIO_Mode_Out_PP;
	
	
	GPIO_Init(GPIOB,&GPIOinit);
	
	GPIO_SetBits(GPIOB,LED);
}
