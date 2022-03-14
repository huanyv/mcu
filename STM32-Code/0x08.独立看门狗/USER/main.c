#include"stm32f10x.h"
#include"led.h"
#include"delay.h"								//Tout=((4×2^prer) ×rlr) /40 
#include"iwdg.h"
#include"key.h"

int main(void) {
	LED_init();
	key_init();
	
	GPIO_SetBits(GPIOB,LED);
	delay_ms(1000);
	
	IWDG_Init(4,625); 				//1S钟的  喂狗时间  1s不喂狗 复位
//	GPIO_ResetBits(GPIOB,LED);
	while(1) {
		if(GPIO_ReadInputDataBit(GPIOA,key1) == 1)//如果 k1 按下 不 喂狗
		{
			delay_ms(10);
			if(GPIO_ReadInputDataBit(GPIOA,key1) == 1)
			IWDG_ReloadCounter();//    喂狗   
		}
		GPIO_ResetBits(GPIOB,LED);
//	delay_ms(200);
//	GPIO_SetBits(GPIOB,LED);
//	delay_ms(200);
//	GPIO_ResetBits(GPIOB,LED);
	}
}





