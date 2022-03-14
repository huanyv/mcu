/*************************
s1:南北   红     东西   绿
s2:南北   红     东西   黄
s3:南北   绿     东西   红
s4:南北   黄     东西   红
*************************/
#include<reg52.h>
typedef unsigned char uchar;
typedef unsigned int uint;

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

uchar sec=30;
uchar flag=1;

void delay(uint iii)
{
	while(iii--);
}
void display()
{
	if(flag==1||flag==2)//状态1和状态2，东西比南北少2秒
	{
		bit_0=0;bit_1=1;
	
		P0=duanxuan[sec%10];
		delay(100);P0=0x00;
		if(sec>2)
		{
			P1=duanxuan[(sec-2)%10];
			delay(200);P1=0x00;
		}
		else
		{
			P1=duanxuan[sec%10];
			delay(200);P1=0x00;
		}
	
		bit_0=1;bit_1=0;
		
		P0=duanxuan[sec/10];
		delay(100);P0=0x00;
		if(sec>2)
		{
			P1=duanxuan[(sec-2)/10];
		    delay(200);P1=0x00;
		}
		else
		{
			P1=duanxuan[sec/10];
			delay(200);P1=0x00;
		} 
	}
	else					 //状态3和状态4，南北比东西少2秒
	{
		bit_0=0;bit_1=1;
	
		P1=duanxuan[sec%10];
		delay(100);P1=0x00;
		if(sec>2)
		{
			P0=duanxuan[(sec-2)%10];
			delay(200);P0=0x00;
		}
		else
		{
			P0=duanxuan[sec%10];
			delay(200);P0=0x00;
		}
	
		bit_0=1;bit_1=0;
		
		P1=duanxuan[sec/10];
		delay(100);P1=0x00;
		if(sec>2)
		{
			P0=duanxuan[(sec-2)/10];
		    delay(200);P0=0x00;
		}
		else
		{
			P0=duanxuan[sec/10];
			delay(200);P0=0x00;
		} 	
	}	
}

void timer_init()
{
	TMOD=0x01;
	EA=1;ET0=1;TR0=1;
	TH0=TH_0;TL0=TL_0;
}
void led_display()
{
	if(flag==1)	//s1
	{
		ew_led_r=0;	
		ew_led_g=1;
		ew_led_y=1;

		ns_led_r=1;
		ns_led_g=0;
		ns_led_y=1;
	}
	else if(flag==2) //s2
	{
		ew_led_r=0;	
		ew_led_g=1;
		ew_led_y=1;

		ns_led_r=1;
		ns_led_g=1;
		ns_led_y=0;
	}
	else if(flag==3) //s3
	{
		ew_led_r=1;	
		ew_led_g=0;
		ew_led_y=1;

		ns_led_r=0;
		ns_led_g=1;
		ns_led_y=1;
	}
	else if(flag==4)	//s4
	{
		ew_led_r=1;	
		ew_led_g=1;
		ew_led_y=0;

		ns_led_r=0;
		ns_led_g=1;
		ns_led_y=1;
	}
	else
	{
		flag=1;//一共四个状态
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
	static uchar jjj=0;
	TH0=TH_0;TL0=TL_0;
	if(++jjj==20)
	{
		jjj=0;
		sec--;
		if(sec==0)
		{
			sec=30;
			flag++;//s3
		
		}		
		if(sec-2==0)
		{
			flag++;//s2	   s4
		}
	}
}
