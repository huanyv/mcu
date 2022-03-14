#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit LCD_RS=P2^6;	  //0 指令       1 数据  
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
	LCD_write_0(0x38);//8位格式，2行，5X7
	delay(150);
	LCD_write_0(0x38);//第二次设置正常显示
	LCD_write_0(0x0c);//整体显示，关光标，光标不闪烁
	LCD_write_0(0x06);//输入方式，增量不位移
	LCD_write_0(0x01);//清屏
	delay(200);
			 
}
/*
void LCD_X_Y(uchar x,uchar y,uchar date)
{
    uchar addr;
    if(x==1)
    {
        addr=0x80+y;
    }
    else
        addr=0xc0+y;
    LCD_write_0(addr);
    LCD_write_1(date);
}	*/

void zidingyi(uchar (*s)[8],uint j,uint j_1)
{
	uint i,i_1;
	for(i_1=1;i_1<=j_1;i_1++)
	{
		if(i_1==1)
			LCD_write_0(0x40);
		if(i_1==2)
			LCD_write_0(0x48);
		if(i_1==3)
			LCD_write_0(0x50);
		if(i_1==4)
			LCD_write_0(0x58);
		if(i_1==5)
			LCD_write_0(0x60);
		if(i_1==6)
			LCD_write_0(0x68);
		if(i_1==7)
			LCD_write_0(0x70);
		if(i_1==8)
			LCD_write_0(0x78);
		for(i=0;i<j;i++)
		{
			LCD_write_1(s[i_1-1][i]);
		}
	}
}

int main()
{
 	uchar code _zidingyi_[2][8]={{0x00,0x17,0x08,0x08,0x08,0x08,0x07,0x00},{0x00,0x00,0x04,0x0E,0x1F,0x0E,0x04,0x00}};				//			 0x10,0x06,0x09,0x08,0x08,0x09,0x06,0x00
	LCD_init();
	zidingyi(_zidingyi_,8,2);
	row(1);
	LCD_write_1(0x00);
	row(2);
	LCD_write_1(0x01);
	while(1);
	return 0;
}