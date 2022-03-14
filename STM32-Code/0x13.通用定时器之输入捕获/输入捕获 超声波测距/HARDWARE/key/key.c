#include "key.h"

void KEY_GPIO_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(KEY_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = KEY_ALL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	
	GPIO_Init(KEY_GPIO,&GPIO_InitStructure);
	
#if   WKUP_ENABLE	
	RCC_APB2PeriphClockCmd(KEY_WKUP_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = KEY_WKUP_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	
	GPIO_Init(KEY_WKUP_GPIO,&GPIO_InitStructure);
#endif
	
}



