#include<lcd1602.h>

void delay_1(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<10;j++);
}

void LCD_write_0(uchar dat)//写入指令
{
	LCD_DB=dat;
	LCD_RS=0;
	LCD_RW=0;
	LCD_E=1;
	LCD_E=0;
	delay_1(1);
}

void LCD_write_1(uchar dat)//定入数据  
{
	LCD_DB=dat;
	LCD_RS=1;
	LCD_RW=0;
	LCD_E=1;
	LCD_E=0;
	delay_1(1);
}
/*
void row(uint i)//自定义显示行
{
uint k;
if(i==1)
k=0x00;
else
k=0x40;
LCD_write_0(0x80|k);
}							*/

void LCD_init()//初始化
{
	LCD_write_0(0x38);
	delay_1(150);
	LCD_write_0(0x38);
	LCD_write_0(0x0c);
	LCD_write_0(0x06);
	LCD_write_0(0x01);
	delay_1(200);
}

void LCD_X_Y(uchar x,uchar y,uchar date)//自定义显示  位置
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
}

void zidingyi(uchar (*s)[8],uchar len,uchar count)//自定义显示  字符   
{											//*s为自定义字符的 二维数组   len每个字符的数组 的长度   count：要自定义的个数
	uchar i,j;								
	for(j=1;j<=count;j++)
	{
		if(j==1)
			LCD_write_0(0x40);
		if(j==2)
			LCD_write_0(0x48);
		if(j==3)
			LCD_write_0(0x50);
		if(j==4)
			LCD_write_0(0x58);
		if(j==5)
			LCD_write_0(0x60);
		if(j==6)
			LCD_write_0(0x68);
		if(j==7)
			LCD_write_0(0x70);
		if(j==8)
			LCD_write_0(0x78);
		for(i=0;i<len;i++)
		{
			LCD_write_1(s[j-1][i]);
		}
	}
}