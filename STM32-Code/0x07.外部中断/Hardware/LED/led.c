#include"stm32f10x.h"
#include"led.h"

void LED_Init(void) {
	GPIO_InitTypeDef GPIO_InitSturcture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitSturcture.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitSturcture.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_7 | GPIO_Pin_1;
;
	GPIO_InitSturcture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitSturcture);
}




