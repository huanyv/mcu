#include"stm32f10x.h"
#include"led.h"
#include"delay.h"
#include"led_display.h"
#include"sys.h"

#define C38 PBout(4)
#define B38 PBout(3)
#define A38 PBout(2)// 38 译码器宏定义

uint8_t table1[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d, 
					0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; //共阴数码管 段选  码表

void display(void) {
	uint8_t i = 0;
	for(i = 0; i < 8; i++) {
		switch(i) {
			case 0:C38 = 0;B38 = 0;A38 = 0;break;
			case 1:C38 = 0;B38 = 0;A38 = 1;break;
			case 2:C38 = 0;B38 = 1;A38 = 0;break;
			case 3:C38 = 0;B38 = 1;A38 = 1;break;
			case 4:C38 = 1;B38 = 0;A38 = 0;break;
			case 5:C38 = 1;B38 = 0;A38 = 1;break;
			case 6:C38 = 1;B38 = 1;A38 = 0;break;
			case 7:C38 = 1;B38 = 1;A38 = 1;break;
		}                                      
		GPIO_Write(GPIOB,GPIO_ReadOutputData(GPIOB) | (table1[8-i]<<8));//不影响其它 位 输出IO口
		delay_ms(1);
		GPIO_Write(GPIOB,GPIO_ReadOutputData(GPIOB) & 0x00ff);//不影响低位消隐
	}
	
}

int main(void) {
	LED_Display_Init();

	while(1) {
		
		display();
		
	}
}









