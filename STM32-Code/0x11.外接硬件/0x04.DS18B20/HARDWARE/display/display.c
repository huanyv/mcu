#include "display.h"
#include "18b20.h"
#include "delay.h"

uint8_t temp_count[7]={0};
uint8_t table[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x40};
void Display_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_Write(GPIOB,0XFFFF);//熄灭灯
}

												
void read_temp(void) {
	int temp;
	float tp;
	temp = Read_Temp();
	if(temp<0) {
		temp_count[0] = 0x40;
	  temp = temp-1;
		temp =~ temp;//负数的补码等于 取反加一，减一取反即为原码
		tp = temp;
		temp = tp*0.0625*100+0.5;
	}
	else { 
		temp_count[0] = 0x00;
		tp = temp;
		temp = tp*0.0625*100+0.5;
	}
	
	if(temp > 9999){
		temp_count[1] = table[temp/10000];
	}
	else{ 
		temp_count[1] = 0x00;
	}
	
	if(temp>999)
		temp_count[2] = table[temp/1000%10];
	else
		temp_count[2] = 0x00;
	
	temp_count[3] = table[temp/100%10] | 0x80;
	temp_count[4] = table[temp/10%10];
	temp_count[5] = table[temp%10];
	temp_count[6] = 0x39;
}

void display(void) {
	uint8_t i;
	read_temp();
	for(i=0;i<8;i++) {
		switch(i) {
			case 0:C38 = 0; B38 = 0; A38 = 0;GPIO_HighWrite(GPIOB,temp_count[6]);break;
			case 1:C38 = 0; B38 = 0; A38 = 1;GPIO_HighWrite(GPIOB,temp_count[5]);break;
			case 2:C38 = 0; B38 = 1; A38 = 0;GPIO_HighWrite(GPIOB,temp_count[4]);break;
			case 3:C38 = 0; B38 = 1; A38 = 1;GPIO_HighWrite(GPIOB,temp_count[3]);break;
			case 4:C38 = 1; B38 = 0; A38 = 0;GPIO_HighWrite(GPIOB,temp_count[2]);break;
			case 5:C38 = 1; B38 = 0; A38 = 1;GPIO_HighWrite(GPIOB,temp_count[1]);break;
			case 6:C38 = 1; B38 = 1; A38 = 0;GPIO_HighWrite(GPIOB,temp_count[0]);break;
			case 7:C38 = 1; B38 = 1; A38 = 1;break;
		}
		delay_ms(1);
	}
}
