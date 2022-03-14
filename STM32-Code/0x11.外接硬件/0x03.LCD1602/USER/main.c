#include "stm32f10x.h"
#include "delay.h"
#include "lcd1602.h"

uint8_t zi[2][8]={{0x10,0x06,0x09,0x08,0x08,0x09,0x06,0x00},//摄氏度图标
									{0x18,0x04,0x02,0x1F,0x02,0x04,0x18,0x00}};//箭头

int main(void) {
	LCD_Init();
	
	LCD_Write_Cmd(0x80);
	LCD_Write_Dat('A');
	
	LCD_X_Y(1,2,'B');
	
	zidingyi(zi,8,2);
	
	LCD_X_Y(2,1,0x00);//自定字符1
	LCD_X_Y(2,2,0x01);//自定字符2
	while(1) {
		GPIO_ReversePin(GPIOB,GPIO_Pin_0);
		delay_ms(500);
	}
}
