#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_E=P2^7;

#define LCD_DB P0

void delay(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
	for(j=0;j<10;j++);
}

void LCD_write_0(uchar dat)
{
	LCD_DB=dat;
	LCD_RS=0;
	LCD_RW=0;
	LCD_E=1;
	LCD_E=0;
	delay(1);
}

void LCD_write_1(uchar dat)
{
	LCD_DB=dat;
	LCD_RS=1;
	LCD_RW=0;
	LCD_E=1;
	LCD_E=0;
	delay(1);
}

void row(uint i)
{
	uint k;
	if(i==1)
	k=0x00;
	else
	k=0x40;
	LCD_write_0(0x80|k);
}

void LCD_init()
{
	LCD_write_0(0x38);
	delay(150);
	LCD_write_0(0x38);
	LCD_write_0(0x0c);
	LCD_write_0(0x06);
	LCD_write_0(0x01);
	delay(200);
}
		/*
void LCD1602_X_Y(uchar x,uchar y,uchar dat)
{
	uchar addr;
	if(x==1)
	{
		addr=0x80+y;
	}
	else
		addr=0xc0+y;
	LCD_write_0(addr);
	LCD_write_1(dat);
}								   */
  
int main()
{
	uchar str[]="liyaolong",i=0;
	LCD_init();
    row(1);
	for(i=0;str[i]!='\0';i++)
	{
		LCD_write_1(str[i]);
		delay(1000);
	} 
	LCD_write_0(0xc0+6);
	LCD_write_0(0x0f);
	
	while(1)
	{
		
	}
	return 0;
}				 