#include<reg52.h>
typedef unsigned char uchar;
typedef unsigned int uint;

#define segment P0

#define count 50000
#define TH_0 (65536-count)/256
#define TL_0 (65536-count)%256

sbit ew_led_r=P3^0;
sbit ew_led_y=P3^1;
sbit ew_led_g=P3^2;
sbit ns_led_r=P3^3;
sbit ns_led_y=P3^4;
sbit ns_led_g=P3^5;

sbit bit_0=P2^0;
sbit bit_1=P2^1;

uchar code duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uint jjj;
uchar sec=60;
uchar flag=0;

void delay(uint iii)
{
	while(iii--);
}
void display()
{
	bit_0=0;bit_1=1;
	segment=duanxuan[sec%10];
	delay(100);segment=0x00;
	
	bit_0=1;bit_1=0;
	segment=duanxuan[sec/10];
	delay(100);segment=0x00;
}

void timer_init()
{
	TMOD=0x01;
	EA=1;ET0=1;TR0=1;
	TH0=TH_0;TL0=TL_0;
}
void led_display()
{
	if(flag==0)
	{
		ew_led_r=0;
		ew_led_y=1;
		ew_led_g=1;
		
		ns_led_r=1;
		ns_led_y=1;
		ns_led_g=0;
	}
	if(flag==1)
	{
		ew_led_r=1;
		ew_led_y=0;
		ew_led_g=1;
		
		ns_led_r=1;
		ns_led_y=0;
		ns_led_g=1;
	}
	if(flag==2)
	{
		ew_led_r=1;
		ew_led_y=1;
		ew_led_g=0;
		
		ns_led_r=0;
		ns_led_y=1;
		ns_led_g=1;
	}
	if(flag==3)
	{
		ew_led_r=1;
		ew_led_y=0;
		ew_led_g=1;
		
		ns_led_r=1;
		ns_led_y=0;
		ns_led_g=1;
	}
}

void main()
{
	timer_init();
	while(1)
	{
		display();
		led_display();
	}
}

void timer0() interrupt 1
{
	TH0=TH_0;TL0=TL_0;
	if(++jjj==20)
	{
		jjj=0;
		sec--;
		if(sec==255)
		{
			flag++;
			if(flag==1)sec=5;
			else if(flag==2)sec=60;
			else if(flag==3)sec=5;

			else
			{
				sec=60;flag=0;
			}
		}
	}
}
