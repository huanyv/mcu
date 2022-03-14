#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit buzzer=P1^5;
//sbit off=P3^2;

void delay(uint iii)
{
	while(iii--);
}

void int0_init()
{
	EA=1;EX0=1;IT0=0;
}

int main()
{
	int0_init();
	while(1)
	{
		
	}
	return 0;
}

void int0() interrupt 0
{
	buzzer=~buzzer;
	delay(75);
}