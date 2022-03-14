#include<reg52.h>
#include<lcd1602.h>

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;

#define count 5000
#define thx (65536-count)>>8
#define tlx	(65536-count)&0x00ff

uchar time[]="00:00:00",i1;
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
void run_time_set_up()
{
	time[0]=min/10+'0';
	time[1]=min%10+'0';
	time[3]=sec/10+'0';
	time[4]=sec%10+'0';
	time[6]=ms/10+'0';
	time[7]=ms%10+'0';
}					//          01234567
int main()			//	time[]="00:00:00"
{
	uint i,j;
	timer0_init();
	LCD_init();
	intr_init();
	while(1)
	{
		j=4;
		run_time_set_up();
		for(i=0;time[i]!='\0';i++)
		{
			LCD_X_Y(1,j++,time[i]);
		}
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
	delay(2000);
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
