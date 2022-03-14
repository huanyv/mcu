#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit k3=P3^2;
sbit led1=P2^0;

void delay(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<60;j++);
}

int main()
{
	IE=0x81;
	TCON=0X01;
	while(1);
	return 0;
}

void zhongduan() interrupt 0
{
	delay(40);
	if(k3==0)
	{
		led1=~led1;	
	}
}