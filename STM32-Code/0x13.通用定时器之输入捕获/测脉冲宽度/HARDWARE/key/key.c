#include "key.h"

void KEY_GPIO_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
	GPIO_InitStructure.GPIO_Pin  = KEY1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(KEY1_GPIO,&GPIO_InitStructure);
	KEY1 = 0;
}



