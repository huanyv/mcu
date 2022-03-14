#include<reg52.h>
#include"key.h"

#define count 50000
#define TH_0  (65536-count)/256
#define TL_0  (65536-count)%256

#define YELLOW_TIME    5
#define TIME_SMALL    20
#define TIME_BIG    60

sbit ew_led_r=P3^0;
sbit ew_led_y=P3^1;
sbit ew_led_g=P3^2;

sbit ns_led_r=P3^3;
sbit ns_led_y=P3^4;
sbit ns_led_g=P3^5;

sbit bit_0=P2^0;
sbit bit_1=P2^1;

uchar code duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};


uchar sec  = 30;
uchar flag = 1;
uchar temp = 30;

bit YELLOW = 0;

void delay(uint iii)
{
	while(iii--);
}
void display()
{
	if(flag==1||flag==2)	//状态1和状态2，东西比南北少2秒
	{
		bit_0=0;bit_1=1;
	
		P0=duanxuan[sec%10];
		delay(100);P0=0x00;
		if(sec>YELLOW_TIME)
		{
			P1=duanxuan[(sec-YELLOW_TIME)%10];
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
		if(sec>YELLOW_TIME)
		{
			P1=duanxuan[(sec-YELLOW_TIME)/10];
		    delay(200);P1=0x00;
		}
		else
		{
			P1=duanxuan[sec/10];
			delay(200);P1=0x00;
		} 
	}
	else if(flag==3||flag==4)//状态3和状态4，南北比东西少2秒
	{
		bit_0=0;bit_1=1;
	
		P1=duanxuan[sec%10];
		delay(100);P1=0x00;
		if(sec>YELLOW_TIME)
		{
			P0=duanxuan[(sec-YELLOW_TIME)%10];
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
		if(sec>YELLOW_TIME)
		{
			P0=duanxuan[(sec-YELLOW_TIME)/10];
		    delay(200);P0=0x00;
		}
		else
		{
			P0=duanxuan[sec/10];
			delay(200);P0=0x00;
		} 	
	}
	else if(flag==6||flag==7||flag==8)	 //路口通行管理
	{
		bit_0=0;bit_1=1;

		P0=0x3f;
		delay(100);P0=0x00;
		P1=0x3f;
		delay(100);P1=0x00;

		bit_0=1;bit_1=0;

		P0=0x3f;
		delay(100);P0=0x00;
		P1=0x3f;
		delay(100);P1=0x00;
	}
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
		if(YELLOW == 0) ns_led_y=0;
		else ns_led_y=1;
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
		if(YELLOW == 0)ew_led_y=0;
		else ew_led_y=1;

		ns_led_r=0;
		ns_led_g=1;
		ns_led_y=1;
	}
	else if(flag==5)	 //回到s1
	{
		flag=1;//一共四个状态
	}
	else if(flag==6)
	{
		ew_led_r=1;	
		ew_led_g=1;
		ew_led_y=0;

		ns_led_r=1;
		ns_led_g=1;
		ns_led_y=0;
	}
	else if(flag==7)
	{
		ew_led_r=1;	
		ew_led_g=0;
		ew_led_y=1;

		ns_led_r=0;
		ns_led_g=1;
		ns_led_y=1;
	}
	else
	{
		ew_led_r=0;	
		ew_led_g=1;
		ew_led_y=1;

		ns_led_r=1;
		ns_led_g=0;
		ns_led_y=1;
	}
}
void key()
{
	uchar k = 0;
	static uchar i=0;
	k = Read_Key();
	if(k==4){
			i++;TR0=0;	
	}
	if(k==3&&TR0==0&&sec<=TIME_BIG&&(flag==1||flag==2||flag==3||flag==4))
	{
			sec=sec+YELLOW_TIME;
			temp=sec;
	}
	if(k==2&&TR0==0&&sec>=TIME_SMALL&&(flag==1||flag==2||flag==3||flag==4))
	{
			sec=sec-YELLOW_TIME;
			temp=sec;
	}
	if(k==1&&(flag==1||flag==2||flag==3||flag==4))
	{
			TR0=~TR0;
	}
	if(i==1){
		flag=6;
	}
	if(i==2){
		flag=7;
	}
	if(i==3){
		flag=8;
	}
	if(i==4){
		flag=1;
		TR0=1; 
		i=0;
	}
}

void YELLOW_TIMEr_init()
{
	TMOD=0x11;
	EA=1;
	ET0=1;TR0=1;
	ET1=1;TR1=1;
	TH0=TH_0;TL0=TL_0;
	TH1=TH_0;TL1=TL_0;
}
void main()
{
	YELLOW_TIMEr_init();
	while(1)
	{
		display();
		led_display();
		key();
	}
}

void YELLOW_TIMEr0() interrupt 1
{
	static uchar jjj=0;
	TH0=TH_0;TL0=TL_0;
	if(++jjj==20)
	{
		jjj=0;
		sec--;
		if(sec==0)
		{
			sec=temp;
			flag++;//s3
		
		}		
		if(sec-YELLOW_TIME==0)
		{
			flag++;//s2	   s4
		}
	}
}

void YELLOW_TIMEr1() interrupt 3
{
	static uchar jjj = 0;
	TH1=TH_0;TL1=TL_0;
	if(++jjj==10){
		jjj = 0;
		YELLOW = ~YELLOW;
	}
}
















