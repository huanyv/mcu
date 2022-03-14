#include"led.h"
#include"stm32f10x.h"

void LED_init(void)
{
	GPIO_InitTypeDef GPIOinit;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);//��GPIO��ʱ�ӣ��ȴ򿪸��ò����޸ĸ��ù���
 	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);     //����JTAG   Ҫ�ȿ�ʱ�ӣ�����ӳ�䣻����ʾ�ر�jtag��ʹ��swd��  
		
	GPIOinit.GPIO_Pin=GPIO_Pin_All;
	GPIOinit.GPIO_Speed=GPIO_Speed_50MHz;
	GPIOinit.GPIO_Mode=GPIO_Mode_Out_PP;
	
	
	GPIO_Init(led,&GPIOinit);
}
