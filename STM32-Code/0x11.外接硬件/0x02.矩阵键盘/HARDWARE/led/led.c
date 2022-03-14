#include"led.h"
#include"stm32f10x.h"

void LED_init(void)
{
	GPIO_InitTypeDef GPIOinit;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIOinit.GPIO_Pin=GPIO_Pin_All;
	GPIOinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIOinit.GPIO_Mode=GPIO_Mode_Out_PP;
	
	
	GPIO_Init(GPIOB,&GPIOinit);
}
