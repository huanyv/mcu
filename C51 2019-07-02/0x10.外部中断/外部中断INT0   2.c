#include<reg52.h>
#include<intrins.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit k3=P3^2;

#define LED P2

void delay(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<60;j++);
}

void left(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
	{
		LED=0xfe;
		for(j=0;j<8;j++)
		{
			delay(1000);
			LED=_crol_(LED,1);
		}
	}	
}

int main()
{
	IE=0x81;
	TCON=0x01;
	while(1)
	{
		LED=~LED;
		delay(100);
	}
	return 0;
}

void zhongduan() interrupt 0
{
	uchar led_before=LED;
	delay(40);
	TCON=0x00;
	left(3);
	TCON=0x01;
	LED=led_before;	
}