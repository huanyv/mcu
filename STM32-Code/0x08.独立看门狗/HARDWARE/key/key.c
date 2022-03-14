#include"key.h"
#include"stm32f10x.h"

void key_init(void){
	GPIO_InitTypeDef GPIOinit;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIOinit.GPIO_Pin=key1;
	GPIOinit.GPIO_Mode=GPIO_Mode_IPU;
	
	GPIO_Init(GPIOA,&GPIOinit);
}

