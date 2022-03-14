#include"stm32f10x.h"
#include"key.h"



void KEY_Init(void) {
	
	GPIO_InitTypeDef GPIO_InitStucture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	GPIO_InitStucture.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStucture.GPIO_Pin   = KEY1 | KEY2 | GPIO_Pin_4;
	GPIO_Init(GPIOA,&GPIO_InitStucture);
}







