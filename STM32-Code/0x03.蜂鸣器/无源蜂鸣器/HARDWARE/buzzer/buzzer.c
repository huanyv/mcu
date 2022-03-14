#include"buzzer.h"
#include"stm32f10x.h"
#include"sys.h"
void buzzer_init(void){
	
	GPIO_InitTypeDef GPIOINIT;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIOINIT.GPIO_Pin=GPIO_Pin_5;
	GPIOINIT.GPIO_Speed=GPIO_Speed_50MHz;
	GPIOINIT.GPIO_Mode=GPIO_Mode_Out_PP;

	GPIO_Init(GPIOA,&GPIOINIT);

	
}
