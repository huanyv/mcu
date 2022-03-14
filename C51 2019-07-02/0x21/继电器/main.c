#include<reg52.h>
typedef unsigned char uchar;
typedef unsigned int uint;

sbit ctrl=P2^0;

void delay(uint iii)
{
	while(iii--);
}

void int0_init()
{
	EA=1;EX0=1;IT0=1;
}

void main()
{
	int0_init();
	while(1)
	{
	
	}
}

void int0() interrupt 0
{
	delay(2000);
	ctrl=~ctrl;
}
