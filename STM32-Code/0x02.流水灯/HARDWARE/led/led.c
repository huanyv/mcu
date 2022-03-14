#include"led.h"
#include"stm32f10x.h"

void LED_init(void)
{
	GPIO_InitTypeDef GPIOinit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);//打开GPIO口时钟，先打开复用才能修改复用功能
 	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);     //禁用JTAG   要先开时钟，再重映射；这句表示关闭jtag，使能swd。  
		
	GPIOinit.GPIO_Pin=GPIO_Pin_All;
	GPIOinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIOinit.GPIO_Mode=GPIO_Mode_Out_PP;
	
	
	GPIO_Init(led,&GPIOinit);
}
