#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit buzzer=P1^5;
sbit off=P3^7;

void delay(uint iii)
{
	while(iii--);
}

void _buzzer_()
{
	buzzer=~buzzer;
	delay(80);
}

int main()
{
	while(1)
	{
		while(off==0)
		{
			_buzzer_();
		}
	}
	return 0;
}