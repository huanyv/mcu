#include<reg51.h>
#include<intrins.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit RCLK=P3^5;
sbit SRCLK=P3^6;
sbit SER=P3^4;											//ÐÄ	 {0x30,0x48,0x44,0x22,0x44,0x48,0x30,0x00}

sbit OUT=P3^2; 

uchar temp[6],time,i1=10;

uchar code ledduan[11][8]={ {0x00,0x00,0x7C,0x82,0x82,0x82,0x7C,0x00}, //0
							{0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00}, //1
							{0x00,0x00,0x4F,0x49,0x49,0x79,0x00,0x00}, //2
							{0x00,0x00,0x49,0x49,0x49,0x7F,0x00,0x00}, //3
							{0x00,0x00,0x78,0x08,0x3E,0x08,0x08,0x00}, //4
							{0x00,0x00,0x79,0x49,0x49,0x4F,0x00,0x00}, //5
							{0x00,0x00,0x7F,0x49,0x49,0x4F,0x00,0x00}, //6
							{0x00,0x00,0x40,0x40,0x40,0x7E,0x00,0x00}, //7
							{0x00,0x00,0x7F,0x49,0x49,0x7F,0x00,0x00}, //8
							{0x00,0x00,0x79,0x49,0x49,0x7F,0x00,0x00}, //9
							{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};//¿Õ

uchar code ledwei[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
uchar code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
						0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0X76};
void delay(uint iii)
{
	while(iii--);
}

void yanshi(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
	for(j=0;j<60;j++);
}


void H595(uchar duan)
{
	uint i;
	SRCLK=0;
	RCLK=0;
	for(i=0;i<8;i++)
	{
		SER=duan>>7;		   //1001 1001
		duan=duan<<1;
		SRCLK=1;
		_nop_();
		_nop_();
		SRCLK=0;
	}
	RCLK=1;
	_nop_();
	_nop_();
	RCLK=0;
}

/*
void display()
{
	uchar i;
	for(i=0;i<3;i++)
	{
		switch(i)
		{
			case 0:LSC=0;LSB=0;LSA=0;
			P0=smgduan[16];break;
			case 1:LSC=0;LSB=0;LSA=1;
			P0=smgduan[temp[2]%16];break;
			case 2:LSC=0;LSB=1;LSA=0;
			P0=smgduan[temp[2]/16];break;
		}
		delay(100);
		P0=0x00;
	}							  
}								 */


void infrared()
{
	uchar i,j;
	uint t;time=0;
	delay(700);
	if(OUT==0)
	{
		t=1000;
		while((OUT==0)&&(t>0))
		{
			delay(1);
			t--;
		}
		if(OUT==1)
		{
			t=500;
			while((OUT==1)&&(t>0))
			{
				delay(1);
				t--;
			}
			for(i=0;i<4;i++)
				for(j=0;j<8;j++)
				{
					t=60;
					while((OUT==0)&&(t>0))
					{
						delay(1);
						t--;
					}
					t=500;
					while((t>0)&&(OUT==1))
					{
						delay(10);
						time++;
						t--;
						if(time>30)
						{
							return;
						}						
					}
					temp[i]=temp[i]>>1;
					if(time>8)
					{
						temp[i]=temp[i]|0x80;
					}
					time=0;
				}
		}
		if(temp[2]!=~temp[3])
		{
			return;
		}		  
	}
}

int main()
{
	uint i;
	OUT=1;
	while(1)
	{
//		display();
		infrared();
		switch(temp[2])
		{
			case 0x16:i1=0;break;
			case 0x0c:i1=1;break;
			case 0x18:i1=2;break;
			case 0x5e:i1=3;break;
			case 0x08:i1=4;break;
			case 0x1c:i1=5;break;
			case 0x5a:i1=6;break;
			case 0x42:i1=7;break;
			case 0x52:i1=8;break;
			case 0x4a:i1=9;break;
			case 0x45:i1=10;break;
		}	
		P0=0x7f;
		for(i=0;i<8;i++)
		{
			P0=ledwei[i];
			H595(ledduan[i1][i]);
			yanshi(2);
			H595(0x00);
		}
	}
	return 0;
}