#include<lcd1602.h>

void delay(uint i_1)
{
	while(i_1--);
}

void lcd1602write_0(uchar dat)
{
	LCD_DB=dat;
	LCD_RS=0;					 
	LCD_RW=0;
	LCD_E=1;
	LCD_E=0;
	delay(8);
}

void lcd1602write_1(uchar dat)
{
	LCD_DB=dat;
	LCD_RS=1;					 
	LCD_RW=0;
	LCD_E=1;
	LCD_E=0;
	delay(8);
}

void lcd1602_X_Y(uchar x,uchar y,uchar dat)
{
	uchar addr;
	if(x==1)
		addr=0x80+y;
	else
		addr=0xc0+y;
	lcd1602write_0(addr);
	lcd1602write_1(dat);
}

void lcd1602init()
{
	 lcd1602write_0(0x38);
	 delay(1500);
	 lcd1602write_0(0x38);
	 lcd1602write_0(0x0c);
	 lcd1602write_0(0x06);
	 lcd1602write_0(0x01);
	 delay(2000);
}