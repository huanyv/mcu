#include<reg52.h>
#include<lcd1602.h>

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

#define count 5000
#define thx (65536-count)>>8
#define tlx	(65536-count)&0x00ff

uchar i1;
uchar code duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uint sec=0,min=0,ms=0;

void delay(uint iii)
{
	while(iii--);
}
void timer0_init()
{
	TMOD=0X01;
	EA=1;ET0=1;TR0=0;
	TH0=thx;TL0=tlx;
}
void intr_init()
{
	EX0=1;EX1=1;
	IT0=1;IT1=1;
}
void display()
{
	uint i;
	for(i=0;i<7;i++)
	{
		switch(i)
		{
			case 1:LSC=0;LSB=0;LSA=0;
			P0=duanxuan[ms%10];break;
			case 2:LSC=0;LSB=0;LSA=1;
			P0=duanxuan[ms/10];break;
			case 3:LSC=0;LSB=1;LSA=0;
			P0=duanxuan[sec%10]|0x80;break;
			case 4:LSC=0;LSB=1;LSA=1;
			P0=duanxuan[sec/10];break;
			case 5:LSC=1;LSB=0;LSA=0;
			P0=duanxuan[min%10]|0x80;break;
			case 6:LSC=1;LSB=0;LSA=1;
			P0=duanxuan[min/10];break;
		}
		delay(100);
		P0=0x00;
	}
}
    				//          01234567
int main()			//	time[]="00:00:00"
{
//	uint i,j;
	timer0_init();
	intr_init();
	while(1)
	{
		 display();
	}
	return 0;
}
void intr0() interrupt 0
{
	delay(2000);
	if(k3==0)
	{
		TR0=~TR0;
	}
}
void intr1() interrupt 2
{
	delay(1000);
	if(k4==0&&TR0==0)
	{
		sec=0;min=0;ms=0;TR0=0;
	}
}
void timer0() interrupt 1
{
	TH0=thx;TL0=tlx;
	if(++i1==2)
	{
		i1=0;
		ms++;
		if(ms==100)
		{
			ms=0;
			sec++;
			if(sec==60)
			{
				sec=0;
				min++;
				if(min==100)
				{
					min=0;
				}
			}
		}	
	}
}
