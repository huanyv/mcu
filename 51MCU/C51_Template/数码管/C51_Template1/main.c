
/*
	定时器 数码管显示 0 - 9
*/

#include<reg52.h>
#define uchar unsigned char;
uchar count = 20;
uchar i = 0;
uchar code tab[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
void main()
{
	TMOD=0X01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;
	P1=0x3f;	
	while(1)
	{	
		if(count >= 20)
		{
			count=0;
			P0 = tab[i];
			i++;
			if(i >= 10)
				i = 0;
		}
	}	
}
void T0_time (void) interrupt 1 
{
	count++;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
}