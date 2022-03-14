#include <reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit led = P2^7;
sbit led2=P2^0;

void main()
{
	TMOD = 0x02;
	EA=1;ET0=1;TR0=1;
	TH0=256-10;
	TL0=256-10;
	led2=0;
	while(1)
	{
	}
}
void timer0() interrupt 1
{
	static uchar i=0;
	i++;
	if(i>=100)
		i=0;
	if(i<5)
		led=0;
	else
		led=1;
}







