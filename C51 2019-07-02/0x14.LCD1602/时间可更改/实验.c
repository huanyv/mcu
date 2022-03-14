#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_E=P2^7;

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;

#define count 50000
#define THx (65536-count)/256
#define TLx (65536-count)%256

#define LCD_DB P0

uint hour=0,minute=0,seconds=0;

uint j;

uchar TIME[]="      TIME";

void delay(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
	for(j=0;j<1;j++);		//10us
}

void kongzhi()
{
	uchar y=0;
	if(k3==0)
	{
		delay(2000);
		if(k3==0)
		{
			seconds++;
			if(seconds==60)
				seconds=0; 
			delay(10000);
		}
	}
	if(k2==0)
	{
		delay(2000);
		if(k2==0)
		{
			minute++;
			if(minute==60)
				minute=0;
			delay(10000); 
		}
	}
	if(k1==0)
	{
		delay(2000);
		if(k1==0)
		{
			hour++;
			if(hour==24)
				hour=0; 
			delay(10000);
		}
	}
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

int main()
{
	uchar i=0,i1=0;
    TH0=THx;TL0=TLx;
    ET0=1;EA=1;TR0=1;TMOD=0x01;
    LCD_init();
	row(1);
	for(i1=0;TIME[i1]!='\0';i1++)
	{
		LCD_write_1(TIME[i1]);
		delay(10);
	}	 
			 
	while(1)
	{     
		row(2);  
		LCD_write_1(' ');
		delay(10);
		LCD_write_1(' ');
		delay(10);
		LCD_write_1(' ');
		delay(10);
		LCD_write_1(' ');
		delay(10);
		LCD_write_1(hour/10+'0');
		delay(10);
		LCD_write_1(hour%10+'0');
		delay(10);
		LCD_write_1(':');
		delay(10);
		LCD_write_1(minute/10+'0');
		delay(10);
		LCD_write_1(minute%10+'0');
		delay(10);
		LCD_write_1(':');
		delay(10);
		LCD_write_1(seconds/10+'0');
		delay(10);
		LCD_write_1(seconds%10+'0');
		delay(10);
		kongzhi();
	delay(5);
	}
	return 0;
}

void time0() interrupt 1			   //¶¨Ê±Æ÷ÖÐ¶Ï  T0
{
	TL0=TLx;TH0=THx;
	if(++j==20)
	{
		j=0;
		seconds++;
		if(seconds==60)
		{
			seconds=0;
			minute++;
			if(minute==60)
			{
				minute=0;
				hour++;
				if(hour==24)
				{
					hour=0;
				}
			}
		}	
	}		
} 