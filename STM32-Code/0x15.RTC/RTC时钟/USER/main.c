#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "rtc.h"

const uint8_t table[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

#define   C38      PBout(4)
#define   B38      PBout(3)
#define   A38      PBout(2)

void GPIO_Display_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIOB->ODR = 0xFFFF;
}

void display(void) {
	uint8_t i;
	for(i=0;i<8;i++) {
		switch(i) {
			case 0: C38 = 0; B38 = 0; A38 = 0; GPIO_High8BitWrite(GPIOB,table[calendar.sec%10]); break;
			case 1: C38 = 0; B38 = 0; A38 = 1; GPIO_High8BitWrite(GPIOB,table[calendar.sec/10]); break;
			case 2: C38 = 0; B38 = 1; A38 = 0; GPIO_High8BitWrite(GPIOB,0x40); break;
			case 3: C38 = 0; B38 = 1; A38 = 1; GPIO_High8BitWrite(GPIOB,table[calendar.min%10]); break;
			case 4: C38 = 1; B38 = 0; A38 = 0; GPIO_High8BitWrite(GPIOB,table[calendar.min/10]); break;
			case 5: C38 = 1; B38 = 0; A38 = 1; GPIO_High8BitWrite(GPIOB,0x40); break;
			case 6: C38 = 1; B38 = 1; A38 = 0; GPIO_High8BitWrite(GPIOB,table[calendar.hour%10]); break;
			case 7: C38 = 1; B38 = 1; A38 = 1; 
			if(calendar.hour >= 10)
				GPIO_High8BitWrite(GPIOB,table[calendar.hour/10]);
			else 
				GPIO_High8BitWrite(GPIOB,0x00); break;
		}
		delay_ms(1);
		GPIO_High8BitWrite(GPIOB,0x00);
	}
}
void key(void) {
	static uint8_t KEY_LETGO = 0;
	static uint8_t KEY_Delay = 0;
	if((KEY1 == 0)&&(KEY_LETGO == 0)) {
		KEY_Delay++;
		if((KEY1 == 0)&&(KEY_Delay > 1)) {
			KEY_LETGO = 1;
			KEY_Delay = 0;
			calendar.hour++;
			if(calendar.hour == 24)
				calendar.hour = 0;
			GPIOB->ODR ^= GPIO_Pin_0;
			RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
		}
	}
	if((KEY2 == 0)&&(KEY_LETGO == 0)) {
		KEY_Delay++;
		if((KEY2 == 0)&&(KEY_Delay > 1)) {
			KEY_LETGO = 1;
			KEY_Delay = 0;
			calendar.min++;
			if(calendar.min == 60)
				calendar.min = 0;
			GPIOB->ODR ^= GPIO_Pin_0;
			RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
		}
	}
	if((KEY3 == 0)&&(KEY_LETGO == 0)){
		KEY_Delay++;
		if((KEY3 == 0)&&(KEY_Delay > 1)) {
			KEY_LETGO = 1;
			KEY_Delay = 0;
			calendar.sec++;
			if(calendar.sec == 60)
				calendar.sec = 0;
			GPIOB->ODR ^= GPIO_Pin_0;
			RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
		}
	}	
	if((KEY1 == 1)&&(KEY2 == 1)&&(KEY3 == 1)&&(KEY4 == 1)){
		KEY_LETGO = 0;KEY_Delay = 0;
	}
}
int main()
{
	Sys_Init();
	RTC_Init();
	GPIO_Display_Init();
	GPIO_KEY_Init();
	while(1) {
		key();
		display();
	}
}





