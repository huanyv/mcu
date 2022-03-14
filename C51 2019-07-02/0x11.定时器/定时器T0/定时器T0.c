#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

#define LED P2
sbit led = P2^1;

uint i=0;

int main()
{
	IE=0x82;
	TR0=1;
	TMOD=0x01;
	TH0=0xFC;
	TL0=0x18;
	while(1);
	return 0;
}

void time0() interrupt 1
{
	TH0=0xFC;
	TL0=0x18;
	if(++i==1000)
	{
		i=0;  led = ~led;
	 	LED=~LED;
	}

}