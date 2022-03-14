#include <STC89C5xRC.H>
typedef unsigned char uchar;
typedef unsigned int uint;
sbit led=P0^0;
void init()
{
	TMOD=0X06;
	TR0=1;EA=1;ET0=1;
	TH0=255;
	TL0=255;
}
int main()
{
	init();
	while(1);
}
void timer0() interrupt 1
{
	led=~led;
}