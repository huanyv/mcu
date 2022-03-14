#include <reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit ON = P1^0;

sbit k1 = P3^1;
sbit k2 = P3^0;
sbit k3 = P3^2;

uchar speed = 20;


void main()
{
	TMOD = 0x02;
	EA=1;ET0=1;TR0=1;
	TH0=256-10;
	TL0=256-10;
	while(1)
	{	
		
		if( k1== 0 ){
			if( k1== 0 ){
				
				speed = 20;		
				
				while(k1 == 0);
			}
	}
	if( k2 == 0 ){
			if( k2== 0 ){
				
				speed = 50;		
				
				while(k2 == 0);
			}
	}
		
	if( k3== 0 ){
			if( k3== 0 ){
				
				speed = 90;		
				
				while(k3 == 0);
			}
	}
		
		
	}
}
void timer0() interrupt 1
{
	static uchar i=0;
	i++;
	if(i>=100)
		i=0;
	if(i<speed)
		ON=1;
	else
		ON=0;
}







