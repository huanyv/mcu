#include "key.h"//GPIO_WriteBit(GPIOB,GPIO_Pin_0,(BitAction)!GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_0));
#include "stm32f10x.h"
#include "display.h"
#include "delay.h"
void key_init(void){
	GPIO_InitTypeDef GPIOinit;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIOinit.GPIO_Pin  = KEY1 | KEY2 | KEY3 | KEY4;
	GPIOinit.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIOinit);
}
void KEY_Contrl(void) {
	static uint8_t key_s = 0;
	static uint8_t KEY_DELAY = 0;
	if(date_flag == 0){
		if((key_s == 0)&&(GPIO_ReadInputDataBit(GPIOA,KEY1) == 0)) {
			KEY_DELAY++;
			if((GPIO_ReadInputDataBit(GPIOA,KEY1) == 0)&&KEY_DELAY>=2) {
				key_s = 1;KEY_DELAY = 0;
				hour++;
				if(hour == 24)hour=0;
			}
		}
		else if((key_s == 0)&&(GPIO_ReadInputDataBit(GPIOA,KEY2) == 0)) {
			KEY_DELAY++;
			if((GPIO_ReadInputDataBit(GPIOA,KEY2) == 0)&&KEY_DELAY>=2) {
				key_s = 1;KEY_DELAY = 0;
				min++;
				if(min == 60) min = 0;
			}
		}
		else if((key_s == 0)&&(GPIO_ReadInputDataBit(GPIOA,KEY3) == 0)) {
			KEY_DELAY++;
			if((GPIO_ReadInputDataBit(GPIOA,KEY3) == 0)&&KEY_DELAY>=2) {
				key_s = 1;KEY_DELAY = 0;
				sec++;
				if(sec == 60) sec = 0;
			}
		}
		else if((key_s == 0)&&(GPIO_ReadInputDataBit(GPIOA,KEY4) == 0)) {
			KEY_DELAY++;
			if((GPIO_ReadInputDataBit(GPIOA,KEY4) == 0)&&KEY_DELAY>=2) {
				key_s = 1;KEY_DELAY = 0;
				date_flag = !date_flag;
			}
		}
	}
	else{
		if((key_s == 0)&&(GPIO_ReadInputDataBit(GPIOA,KEY1) == 0)) {
			KEY_DELAY++;
			if((GPIO_ReadInputDataBit(GPIOA,KEY1) == 0)&&KEY_DELAY>=2) {
				key_s = 1;KEY_DELAY = 0;
				year++;
				if(year == 100)year=0;
			}
		}
		else if((key_s == 0)&&(GPIO_ReadInputDataBit(GPIOA,KEY2) == 0)) {
			KEY_DELAY++;
			if((GPIO_ReadInputDataBit(GPIOA,KEY2) == 0)&&KEY_DELAY>=2) {
				key_s = 1;KEY_DELAY = 0;
				month++;
				if(month == 13) month = 0;
			}
		}
		else if((key_s == 0)&&(GPIO_ReadInputDataBit(GPIOA,KEY3) == 0)) {
			KEY_DELAY++;
			if((GPIO_ReadInputDataBit(GPIOA,KEY3) == 0)&&KEY_DELAY>=2) {
				key_s = 1;KEY_DELAY = 0;
				day++;
				if(day == 32) day = 0;
			}
		}
		else if((key_s == 0)&&(GPIO_ReadInputDataBit(GPIOA,KEY4) == 0)) {
			KEY_DELAY++;
			if((GPIO_ReadInputDataBit(GPIOA,KEY4) == 0)&&KEY_DELAY>=2) {
				key_s = 1;KEY_DELAY = 0;
				date_flag = !date_flag;
			}
		}
	}
	if((GPIO_ReadInputDataBit(GPIOA,KEY1)==1)&&(GPIO_ReadInputDataBit(GPIOA,KEY2)==1))
		if((GPIO_ReadInputDataBit(GPIOA,KEY3)==1)&&(GPIO_ReadInputDataBit(GPIOA,KEY4)==1))
			key_s=0;
		
}






