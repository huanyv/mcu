#include <reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit A38=P2^2;
sbit B38=P2^3;
sbit C38=P2^4;

sbit k1=P3^1;

uchar sec=0,sec2=0;

void delay(uint i)
{
	while(i--);
}
void display()
{
	uchar code duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	uchar i=0;
	for(i=0;i<8;i++)
	{
		switch(i)
		{
			case 0:C38=0;B38=0;A38=0;
			P0=duanxuan[sec%10];
			break;
			case 1:C38=0;B38=0;A38=1;
			P0=duanxuan[sec/10];
			break;
			case 2:C38=0;B38=1;A38=0;
			P0=0x00;
			break;
			case 3:C38=0;B38=1;A38=1;
			P0=0x00;
			break;
			case 4:C38=1;B38=0;A38=0;
			P0=0x00;
			break;
			case 5:C38=1;B38=0;A38=1;
			P0=0x00;
			break;
			case 6:C38=1;B38=1;A38=0;
			P0=duanxuan[sec2%10];
			break;
			case 7:C38=1;B38=1;A38=1;
			P0=duanxuan[sec2/10];
			break;
		}
		delay(100);
		P0=0x00;
	}
}
void key()
{
	static bit flag_s=0;
	if(k1==0&&flag_s==0)
	{
		delay(1000);
		if(k1==0)
		{
			flag_s=1;
			sec++;
			if(sec==100)sec=1;
		}
	}
	if(k1==1)
	{
		flag_s=0;
	}
}
void timer_init()
{
	TMOD|=0x01;
	EA=1;ET0=1;TR0=1;
	TH0=(65536-5000)/256;
	TL0=(65536-5000)%256;
}
void main()
{
	timer_init();
	while(1)
	{
		key();
		display();
	}
}
void time0() interrupt 1
{
	static uchar i=0;
	TH0=(65536-5000)/256;
	TL0=(65536-5000)%256;
	if(++i==20)
	{
		sec2++;
		if(sec2==100)sec2=0;
	}
}