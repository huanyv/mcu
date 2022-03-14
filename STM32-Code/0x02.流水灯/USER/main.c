#include"stm32f10x.h"
#include"led.h"
#include"delay.h"
int main(void)
{
//	unsigned int dat=0;
	unsigned int i=0;
	LED_init();
	delay_init();
	while(1)
	{
//		dat=0xfffe;
//		for(i=0;i<8;i++)
//		{
//			GPIO_Write(led,dat);
//			delay_ms(400);
//			dat=dat<<1|0x0001;
//		}
		for(i=0;i<8;i++) {
			GPIO_Write(GPIOB,~(1<<i));
			delay_ms(300);
		}
	}
}
