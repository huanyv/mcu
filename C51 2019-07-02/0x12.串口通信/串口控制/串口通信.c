#include<reg52.h>
#include<intrins.h>
typedef unsigned char uchar;
typedef unsigned int uint;

sbit F=P1^5;
#define led	P2

uchar flag=0;

void delay(uint i)
{
	while(i--);
}
int main()
{
	SM0=0;SM1=1;REN=1;
	ES=1;
	TMOD=0x20;
	TH1=0xf3;TL1=0xf3;
	TR1=1;
	EA=1; PCON=0x80;
	while(1)
	{
		if(flag==3)
		{
			led=~led;
			delay(30000);
			
		}
		if(flag==1)
		{
			led=0xfe;
			delay(30000);
			led=0xff;
			delay(30000);
		}
		if(flag==2)
		{
			F=0;
			delay(100);
			F=1;
			delay(100);
		}
	}
}

void chuanko() interrupt 4
{
	uchar temp=0;
	if(RI)
	{
		RI=0;
		temp=SBUF;
		if(temp=='1')
		{
			flag=1;
		}
		else if(temp=='2')
		{
			flag=2;
		}
		else if(temp=='3')
		{
			flag=3;
		}
		else
			flag=0;
		SBUF='!';
	}	
	if(TI)
	{
		TI=0;
	}
	
}