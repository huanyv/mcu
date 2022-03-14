#include<reg52.h>

#define     uint       unsigned int
#define     uchar      unsigned char

#define     LED        P2

void delayms(uint i)
{
	uint a, b;
	for(a = 0; a < i; a++)
	{
		for(b = 0; b < 123; b++);
	}
}

int main(void)
{
	uint i = 0;
	for(i = 0; i < 8; i++)
	{
		LED = ~(0x01 << i);
		delayms(500);
	}	
	return 0;
}