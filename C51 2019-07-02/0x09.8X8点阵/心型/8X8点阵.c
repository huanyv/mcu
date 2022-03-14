#include<reg51.h>
#include<intrins.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit RCLK=P3^5;
sbit SRCLK=P3^6;
sbit SER=P3^4;

uchar code ledduan[8]={0x30,0x48,0x44,0x22,0x44,0x48,0x30,0x00};//{0x00,0x00,0x3e,0x41,0x41,0x41,0x3e,0x00};

uchar code ledwei[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};

void yanshi(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
	for(j=0;j<60;j++);
}

void H595(uchar duan)
{
	uint i;
	SRCLK=0;
	RCLK=0;
	for(i=0;i<8;i++)
	{
		SER=duan>>7;		   //1001 1001
		duan=duan<<1;
		SRCLK=1;
		_nop_();
		_nop_();
		SRCLK=0;
	}
	RCLK=1;
	_nop_();
	_nop_();
	RCLK=0;
}

int main()
{
	uint i;
	while(1)
	{
		P0=0x7f;
		for(i=0;i<8;i++)
		{
			P0=ledwei[i];
			H595(ledduan[i]);
			yanshi(2);
			H595(0x00);
		}
	}
	return 0;
}
