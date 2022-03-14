#include<reg52.h>
typedef unsigned char uchar;
typedef unsigned int uint;

#define date P0
#define count 50000
#define TH_0 (65536-count)/256
#define TL_0 (65536-count)%256

sbit dula=P2^0;
sbit wela=P2^1;

unsigned char code distab[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d, 
																0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
uint sec=0,min=0,hour=0;

void delay(uint iii)
{
	while(iii--);
}

void display()
{
	uchar j=0,dat;
	for(dat=0xfe;dat!=0xbf;dat=dat<<1|0x01)
	{
		wela=1;
		date=dat;
		wela=0;
		
		dula=1;
		switch(dat)
		{
			case 0xfe:date=distab[sec%10];break;
			case 0xfd:date=distab[sec/10];break;
			case 0xfb:date=distab[min%10]|0x80;break;
			case 0xf7:date=distab[min/10];break;
			case 0xef:date=distab[hour%10]|0x80;break;
			case 0xdf:date=distab[hour/10];break;			
		}
		dula=0;
		
		dula=1;          //Ïû
		delay(100);
		date=0x00;
		dula=0;		   	//Òþ
	}
	
}
void timer0_init()
{
	TMOD=0x01;
	EA=1;ET0=1;TR0=1;
	TH0=TH_0;TL0=TL_0;
}
void main()
{
	timer0_init();
	while(1)
	{	
		display();
	}
}
void timer0() interrupt 1
{
	static uchar j;
	TH0=TH_0;TL0=TL_0;
	if(++j==20)
	{
		j=0;
		sec++;
		if(sec==60)
		{
			sec=0;
			min++;
			if(min==60)
			{
				min=0;
				hour++;
				if(hour==24)
				{
					hour=0;
				}
			}
		}
	}
}
