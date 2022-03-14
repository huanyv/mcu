#include "display.h"
#include "delay.h"

//uint8_t sec=0;
//uint8_t min=0;
//uint8_t hour=0;
//uint8_t year=0;
//uint8_t month=0;
//uint8_t day=0;

uint8_t date_flag=0;
uint8_t sec=52;
uint8_t min=59;
uint8_t hour=23;
uint8_t year=9;
uint8_t month=2;
uint8_t day=28;

uint8_t distab[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
												0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void Display_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
uint8_t leapyear() {
	uint8_t flag = 0;
	if(year%400==0||(year%4==0&&year%100!=0)) {
		flag = 1;
	}
	else
		flag = 0;
	return flag;
}
uint8_t dat_count(void) {
	uint8_t count = 0;
	if(month != 2) {
		if(month == 4 || month == 6 || month == 9 || month == 11) {
			count = 30;
		}
		if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
			count = 31;
		}
	}
	else {
		if(leapyear() == 1)
			count = 29;
		else
			count = 28;
	}
		return count;	
}
void Display_GPIO_Write(uint8_t dat) {
	GPIO_Write(GPIOB,GPIO_ReadOutputData(GPIOB) & 0X00FF);
	GPIO_Write(GPIOB,GPIO_ReadOutputData(GPIOB) | (dat<<8) );
}
void display(void) {
	uint8_t i;
	if(date_flag == 0) {
		for(i=0;i<8;i++) {
			switch(i) {
				case 0:C38 = 0; B38 = 0; A38 = 0;Display_GPIO_Write(distab[sec%10]);break;
				case 1:C38 = 0; B38 = 0; A38 = 1;Display_GPIO_Write(distab[sec/10]);break;
				case 2:C38 = 0; B38 = 1; A38 = 0;Display_GPIO_Write(0x40);break;
				case 3:C38 = 0; B38 = 1; A38 = 1;Display_GPIO_Write(distab[min%10]);break;
				case 4:C38 = 1; B38 = 0; A38 = 0;Display_GPIO_Write(distab[min/10]);break;
				case 5:C38 = 1; B38 = 0; A38 = 1;Display_GPIO_Write(0x40);break;
				case 6:C38 = 1; B38 = 1; A38 = 0;Display_GPIO_Write(distab[hour%10]);break;
				case 7:C38 = 1; B38 = 1; A38 = 1;
				if(hour>9)Display_GPIO_Write(distab[hour/10]);
				else Display_GPIO_Write(0x00);break;
			}
			delay_ms(1);
		}
	}
		if(date_flag == 1) {
		for(i=0;i<8;i++) {
			switch(i) {
				case 0:C38 = 0; B38 = 0; A38 = 0;Display_GPIO_Write(distab[day%10]);break;
				case 1:C38 = 0; B38 = 0; A38 = 1;
				if(day>9)Display_GPIO_Write(distab[day/10]);
				else Display_GPIO_Write(0x00);break;
				case 2:C38 = 0; B38 = 1; A38 = 0;Display_GPIO_Write(distab[month%10] | 0x80);break;
				case 3:C38 = 0; B38 = 1; A38 = 1;
				if(month>9)Display_GPIO_Write(distab[month/10]);
				else Display_GPIO_Write(0x00);break;
				case 4:C38 = 1; B38 = 0; A38 = 0;Display_GPIO_Write(distab[year%10] | 0x80);break;
				case 5:C38 = 1; B38 = 0; A38 = 1;Display_GPIO_Write(distab[year/10]);break;
				case 6:C38 = 1; B38 = 1; A38 = 0;Display_GPIO_Write(distab[0]);break;
				case 7:C38 = 1; B38 = 1; A38 = 1;Display_GPIO_Write(distab[2]);break;
			}
			delay_ms(1);
		}
	}
}


void TIM2_IRQHandler(void) {
	sec++;
	if(sec == 60) {
		sec = 0;
		min++;
		if(min == 60) {
			min = 0;
			hour++;
			if(hour == 24) {
				hour = 0;
				day++;
				if(day == dat_count()+1){
					day = 1;
					month++;
					if(month == 13) {
						month = 1;
						year++;
						if(year == 100) {
							year = 0;
						}
					}
				}
			}
		}
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}












