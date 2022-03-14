#include "display.h"
#include "key.h"
#include "delay.h"

uint8_t led_dis[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d, 
							0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x40};

void GPIO_Display_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIOB->ODR = 0XFFFF;//ÃðµÆ
}
void display(void) {
	uint8_t i = 0;
	for(i=0;i<8;i++) {
		switch(i) {
			case 0:C38 = 0; B38 = 0; A38 = 0;
				GPIO_High8BitWrite(GPIOB,led_dis[number%10]);break;
			case 1:C38 = 0; B38 = 0; A38 = 1;
				GPIO_High8BitWrite(GPIOB,led_dis[number/10%10]);break;
			case 2:C38 = 0; B38 = 1; A38 = 0;
				GPIO_High8BitWrite(GPIOB,0X00);break;
			case 3:C38 = 0; B38 = 1; A38 = 1;
				GPIO_High8BitWrite(GPIOB,0X00);break;
			case 4:C38 = 1; B38 = 0; A38 = 0;
				GPIO_High8BitWrite(GPIOB,0X00);break;
			case 5:C38 = 1; B38 = 0; A38 = 1;
				GPIO_High8BitWrite(GPIOB,0X00);break;
			case 6:C38 = 1; B38 = 1; A38 = 0;
				GPIO_High8BitWrite(GPIOB,0X00);break;
			case 7:C38 = 1; B38 = 1; A38 = 1;
				GPIO_High8BitWrite(GPIOB,0X00);break;
		}
		delay_ms(2);
		GPIO_High8BitWrite(GPIOB,0X00);
	}
	
}
