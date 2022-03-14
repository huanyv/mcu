#include<reg52.h>
#include<intrins.h>
typedef unsigned char uchar;
typedef unsigned int uint;

#define date P0
#define count 50000
#define TH_0 (65536-count)/256
#define TL_0 (65536-count)%256

sbit ds=P0^0;
sbit clk=P0^1;

uchar diss[8];
uchar code distab[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d, 
																0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x40};
uint sec=58,min=59,hour=9;

void delay(uint iii)
{
	while(iii--);
}
void hc164(uchar dat1)
{
	uchar i=0;
	for(i=0;i<8;i++)
	{
		clk=0;
		ds=dat1>>7;
		dat1=dat1<<1;
		clk=1;
		_nop_();
		_nop_();
	}
}

void display()
{
	uchar i=0,dat=0;
	for(dat=0xfe;dat!=0xff;dat=dat<<1|0x01)
	{
		delay(100);
		hc164(distab[diss[7-i++]]);
		
		hc164(dat);


		
		if(i==8)i=0;
		delay(500);
	}
}
void disss()
{
	diss[0]=hour/10;
	diss[1]=hour%10;
	diss[2]=16;
	diss[3]=min/10;
	diss[4]=min%10;
	diss[5]=16;
	diss[6]=sec/10;
	diss[7]=sec%10;
}
void timer0_init()
{
	TMOD=0x01;
	EA=1;ET0=1;TR0=1;
	TH0=TH_0;TL0=TL_0;
}
void main()
{
	timer0_init();
	while(1)
	{	
		display();
		disss();
	}
}
void timer0() interrupt 1
{
	static uchar j;
	TH0=TH_0;TL0=TL_0;
	if(++j==20)
	{
		j=0;
		sec++;
		if(sec==60)
		{
			sec=0;
			min++;
			if(min==60)
			{
				min=0;
				hour++;
				if(hour==24)
				{
					hour=0;
				}
			}
		}
	}
}
