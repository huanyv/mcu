#include<reg52.h>

#define   uint     unsigned int
#define   uchar     unsigned char
	
sbit k1 = P0^0;

sbit dc = P1^0;




void delay(uint i)
{
	int a, b;
	for(a = 0; a < i; a++)
		for(b = 0; b < 123; b++);
}
int main(void) 
{
	if(k1 == 0) 
	{
		//delay(1000);
		if(k1 == 0)
		{
			dc = ~dc;
		}
		while(k1 == 0);
	}
	return 0;
}











