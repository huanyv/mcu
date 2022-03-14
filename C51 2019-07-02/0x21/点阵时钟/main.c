#include<reg52.h>
#include<intrins.h>
typedef unsigned char uchar;
typedef unsigned int uint;

#define count 50000
#define THx (65536-count)/256
#define TLx (65536-count)%256

sbit stcp=P3^5;
sbit shcp=P3^6;
sbit ds=P3^4;

sbit k1=P3^2;
sbit k2=P3^3;

uchar sec=0,hour=0,min=0;
uchar flag=0;



void delay(uint i)
{
	while(i--);
}
void hc595(uchar dat)
{
	uchar i=0;
	shcp=0;
	stcp=0;
	for(i=0;i<8;i++)
	{
		ds=dat>>7;
		dat=dat<<1;
		shcp=1;
		_nop_();
		_nop_();
		shcp=0;
	}
	stcp=1;
	_nop_();
	_nop_();
	stcp=0;
}
void display()
{
	uchar code table[10][4]={{0x3C,0x42,0x42,0x3C},//0
						   	  {0x00,0x00,0x7E,0x00},//1
							  {0x4E,0x4A,0x4A,0x7A},//2
							  {0x4A,0x4A,0x4A,0x7E},//3
							  {0x18,0x28,0x7E,0x08},//4
						 	  {0x7A,0x4A,0x4A,0x4E},//5
							  {0x7E,0x4A,0x4A,0x4E},//6
							  {0x40,0x40,0x4E,0x70},//7
							  {0x7E,0x4A,0x4A,0x7E},//8
							  {0x7A,0x4A,0x4A,0x7E},};//9
	uchar i=0;
	P0=0x7f;
	for(i=0;i<4;i++)
	{	
		if(flag==3)hc595(table[hour/10][i]<<1|0x01);
		else hc595(table[hour/10][i]<<1);
		delay(100);
		hc595(0x00);
		P0=P0>>1|0x80;	
	}
	for(i=0;i<4;i++)
	{
		if(flag==3)hc595(table[hour%10][i]<<1|0x01);
		else hc595(table[hour%10][i]<<1);
		delay(100);
		hc595(0x00);
		P0=P0>>1|0x80;	
	}
	
	P1=0x7f;
	for(i=0;i<4;i++)
	{
		if(flag==2)hc595(table[min/10][i]<<1|0x01);
		else hc595(table[min/10][i]<<1);
		delay(100);
		hc595(0x00);
		P1=P1>>1|0x80;	
	}
	for(i=0;i<4;i++)
	{
		if(flag==2)hc595(table[min%10][i]<<1|0x01);
		else hc595(table[min%10][i]<<1);
		delay(100);
		hc595(0x00);
		P1=P1>>1|0x80;	
	}
	
	P2=0x7f;
	for(i=0;i<4;i++)
	{
		if(flag==1)hc595(table[sec/10][i]<<1|0x01);
		else hc595(table[sec/10][i]<<1);
		delay(100);
		hc595(0x00);
		P2=P2>>1|0x80;	
	}
	for(i=0;i<4;i++)
	{
		if(flag==1)hc595(table[sec%10][i]<<1|0x01);
		else hc595(table[sec%10][i]<<1);
		delay(100);
		hc595(0x00);
		P2=P2>>1|0x80;	
	}
														
}
void timer_init()
{
	TMOD=0X01;
	EA=1;ET0=1;TR0=1;
	TH0=THx;TL0=TLx;
}
void int0_1_init()
{
	IT0=1;IT1=1;
	EX0=1;EX1=1;
	EA=1;
}
void main()
{
	int0_1_init();
	timer_init();
	while(1)
	{
		display();
	}
}
void timer0() interrupt 1
{
	static uchar i=0;
	TH0=THx;TL0=TLx;
	if(++i==20)
	{
		i=0;
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
void int0() interrupt 0
{
	delay(1500);
	if(k1==0)
	{
		if(flag==1)
		{
			sec++;
			if(sec==60)sec=0;
		}
		if(flag==2)
		{
			min++;
			if(min==60)min=0;
		}
		if(flag==3)
		{
			hour++;
			if(hour==24)hour=0;
		}
	}
}
void int1() interrupt 2
{
	delay(1500);
	if(k2==0)
	{
		flag++;
	}
	if(flag==1)
	{
		TR0=0;
	}
	if(flag==4)
	{
		flag=0;
		TR0=1;
	}
}










