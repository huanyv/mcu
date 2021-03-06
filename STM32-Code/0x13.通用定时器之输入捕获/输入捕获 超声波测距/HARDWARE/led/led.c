#include "led.h"


void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin   = LED0_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	
	GPIO_Init(LED0_GPIO,&GPIO_InitStructure);
	GPIO_Init(LED1_GPIO,&GPIO_InitStructure);
	GPIOB->BSRR = LED0_PIN; // ????
	GPIOE->BSRR = LED1_PIN; // ????
}




