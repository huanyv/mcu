#include<reg52.h>
typedef unsigned char uchar;
typedef unsigned int uint;

#define count 1
#define THx (65536-count)/256
#define TLx (65536-count)%256

sbit PWM=P2^1;
sbit k1=P3^1;
sbit k2=P3^0;

uint zhouqi,zhankongbi,c,flag=20;
bit s;

void delay(uint i)
{
	uint x,y;
	for(x=0;x<i;x++)
	   for(y=0;y<55;y++);
}

void time0init()
{
	TMOD=0x01;
	TH0=THx;TL0=TLx;
	EA=1;ET0=1;TR0=1;
}

void anjian()
{
	 if(k1==0)
	 {
	 	delay(2);
		if(k1==0)
		{
			flag=flag-5;
			while(!k1);
		}
	 }
	 if(k2==0)
	 {
	 	delay(2);
		if(k2==0)
		{
			flag=flag+5;
			while(!k2);
		}
	 }
}

int main()
{
	time0init();
	while(1)
	{
		anjian();
		if(zhankongbi>flag)
		{
			zhankongbi=0;
			if(s==1)
			{
				c++;
			}
			if(s==0)
			{
				c--;
			}
			
		} 
		if(c==1000)
		{
			s=0;
		}
		if(c==0)
		{
			s=1;
		}
		if(zhouqi>1000)
		{
			zhouqi=0;
		}
		if(zhouqi<c)
		{
			PWM=1;
		}
		else
		{
			PWM=0;
		}
	}
	return 0;
}

void time0() interrupt 1
{
	TH0=THx;TL0=TLx;
	zhouqi++;zhankongbi++;
}



