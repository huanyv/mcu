#include"reg52.h"
#include"DHT11.h"
#include"lcd1602.h"


void display() {
	int temp;
	int hum;
	receive(&temp,&hum);
	
	
	LCD_X_Y(1,0,(temp/256/10)+48);//温度整数部分
	LCD_X_Y(1,1,(temp/256%10)+48);
	LCD_X_Y(1,2,'.');
	LCD_X_Y(1,3,(temp%256/10)+48);//温度小数部分
	LCD_X_Y(1,4,(temp%256%10)+48);
	LCD_X_Y(1,5,0x00);//温度 符号
	
	LCD_X_Y(2,0,(hum/256/10)+48);//湿度整数部分
	LCD_X_Y(2,1,(hum/256%10)+48);
	LCD_X_Y(2,2,'.');
	LCD_X_Y(2,3,(hum%256/10)+48);//湿度小数部分
	LCD_X_Y(2,4,(hum%256%10)+48);
	LCD_X_Y(2,5,'%');//湿度 符号
}

void main(void) {
	LCD_init();
    while(1) {
			display();
    }
}












