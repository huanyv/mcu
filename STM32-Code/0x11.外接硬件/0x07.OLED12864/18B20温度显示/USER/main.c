#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "i2c.h"
#include "18b20.h"
#include "OLED_I2C.h"

int distab[7];

void Temp(void)
{
	int temp = 0;
	float tt;
	temp = Read_Temp();
	if(temp<0) {
		distab[0] = 12;
		temp = temp - 1;
		temp = ~temp;
		tt  = temp;
		temp = tt * 0.0625*100+0.5;
	}
	else
	{
		distab[0] = 10;
		tt=temp;
		temp=tt*0.0625*100+0.5;
	}
	distab[1] = temp/1000%10;
	distab[2] = temp/100%10;
	distab[3] = 15;
	distab[4] = temp/10%10;
	distab[5] = temp%10;
	distab[6] = 14;
}

int main(void) {
	uint16_t i = 0;
	
	GPIO_18B20_Init();
	GPIO_I2C_Init();
	OLED_Init();
	OLED_CLS();
	for(i=0;i<2;i++) {
		OLED_ShowCN(48+i*16,0,i);
	}
	while(1) {
		Temp();
		OLED_Show16x32(0, 4,distab[0]);
		OLED_Show16x32(16,4,distab[1]);
		OLED_Show16x32(32,4,distab[2]);
		OLED_Show16x32(48,4,distab[3]);
		OLED_Show16x32(64,4,distab[4]);
		OLED_Show16x32(80,4,distab[5]);
		OLED_Show16x32(96,4,distab[6]);
	} 
}



