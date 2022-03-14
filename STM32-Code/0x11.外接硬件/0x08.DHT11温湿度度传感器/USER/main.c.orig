#include"stm32f10x.h"
#include"led.h"
#include"key.h"
#include"delay.h"

#define uchar unsigned char
#define uint unsigned int

int main(void){
	static uchar KEY_SONG=0;
	LED_init();
	key_init();
	delay_init();
	while(1){
		if(GPIO_ReadInputDataBit(GPIOA,key1)==0&&KEY_SONG==0){
			delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOA,key1)==0){
				KEY_SONG=1;
				GPIO_WriteBit(GPIOB,led,(BitAction)(!GPIO_ReadOutputDataBit(GPIOB,led)));
			}
		}
		if(GPIO_ReadInputDataBit(GPIOA,key1)==1){
			KEY_SONG=0;
		}
	}
}
