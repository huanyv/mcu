#include<reg52.h>

#define uint unsigned int
#define uchar unsigned char
	
sbit k1=P3^2;
sbit k2=P3^3;
sbit k3=P3^1;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

#define count 5000
#define thx (65536-count)>>8
#define tlx	(65536-count)&0x00ff


typedef struct 
{
	uchar ms;
	uchar sec;
	uchar min;
}RECORD_TypeDef; // 时间记录结构体

RECORD_TypeDef RECORD_Structure[10]; // 定义时间记录结构体



uchar code duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

uint sec=0,min=0,ms=0;

uchar MENU1;

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
	for(i=0;i<9;i++)
	{
		if(MENU1 == 0) {
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
				case 7:LSC=1;LSB=1;LSA=0;
				P0=0x00;break;
				case 8:LSC=1;LSB=1;LSA=1;
				P0=0x00;break;
			}
			delay(100);
			P0=0x00;
		}
		else {
			switch(i)
			{
				case 1:LSC=0;LSB=0;LSA=0;
				P0=duanxuan[RECORD_Structure[MENU1-1].ms%10];break;
				case 2:LSC=0;LSB=0;LSA=1;
				P0=duanxuan[RECORD_Structure[MENU1-1].ms/10];break;
				case 3:LSC=0;LSB=1;LSA=0;
				P0=duanxuan[RECORD_Structure[MENU1-1].sec%10]|0x80;break;
				case 4:LSC=0;LSB=1;LSA=1;
				P0=duanxuan[RECORD_Structure[MENU1-1].sec/10];break;
				case 5:LSC=1;LSB=0;LSA=0;
				P0=duanxuan[RECORD_Structure[MENU1-1].min%10]|0x80;break;
				case 6:LSC=1;LSB=0;LSA=1;
				P0=duanxuan[RECORD_Structure[MENU1-1].min/10];break;
				case 7:LSC=1;LSB=1;LSA=0;
				P0=0x40;break;
				case 8:LSC=1;LSB=1;LSA=1;
				P0=duanxuan[MENU1-1];break;
			}
			delay(100);
			P0=0x00;
		}
		
		
	}
}



void key(void) {
	static KEY_LETGO = 0;
	if((k3 == 0)&&(KEY_LETGO == 0)) {
		delay(1000);
		if(k3 == 0) {
			KEY_LETGO = 1;
			MENU1++;
			if(MENU1 == 11)MENU1 = 0;
		}
	}
	if(k3 == 1)
		KEY_LETGO = 0;
}


int main(void)	
{
	uchar i;
	timer0_init();
	intr_init();
	
	for(i = 0; i<10; i++) {
			RECORD_Structure[i].ms  = 0;
			RECORD_Structure[i].sec = 0;
			RECORD_Structure[i].min = 0;
	}
	
	while(1) {
		 display();
		 key();
	}
}
void intr0() interrupt 0
{
	delay(2000);
	if(k1==0) {
		TR0=~TR0;
	}
}
void intr1() interrupt 2
{
	uchar i = 0;
	static uchar j = 0;
	delay(1000);
	if(k2==0&&TR0==0)
	{
		sec=0;min=0;ms=0;TR0=0;
		for(i = 0; i<10; i++) {
			RECORD_Structure[i].ms  = 0;
			RECORD_Structure[i].sec = 0;
			RECORD_Structure[i].min = 0;
		}
	}
	if(k2==0&&TR0==1)
	{
		RECORD_Structure[j].ms  = ms;
		RECORD_Structure[j].sec = sec;
		RECORD_Structure[j].min = min;
		j++;
		if(j == 10)j=0;
	}
}
void timer0() interrupt 1
{
	static uchar i = 0;
	TH0=thx;TL0=tlx;
	if(++i==2)
	{
		i=0;
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
