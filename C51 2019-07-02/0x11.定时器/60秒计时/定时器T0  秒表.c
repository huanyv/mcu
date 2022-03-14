#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit LA=P2^2;
sbit LB=P2^3;
sbit LC=P2^4;
sbit k1=P3^1;

uchar duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uchar saomiao[]={0x3f,0x3f};

uint seconds=0,i=0;


void yanshi(uint i)
{
	while(i--);
}

void kongzhi()
{
	if(k1==0)
	{
		yanshi(2000);
		seconds++;
		if(seconds==59)seconds=0; 
		while(!k1);
	}
}

void weixuan()
{
	uint i;
	for(i=0;i<2;i++)
	{
		switch(i)
		{
			case 0:LC=0;LB=0;LA=0;
			P0=duanxuan[seconds%10];break;
			case 1:LC=0;LB=0;LA=1;
			P0=duanxuan[seconds/10];break;
		}
		yanshi(1000);
		P0=0x00;
	}
}

int main()
{
	IE=0x82;
	TR0=1;
	TMOD=0x01;
	TL0=0x18;TH0=0xFC;
	while(1)
	{
		weixuan();
		kongzhi();
	}		
	return 0;
}

void time0() interrupt 1
{
	TL0=0x18;TH0=0xFC;
	if(++i==1000)
	{
		i=0;
		if(seconds<59)
			seconds++;
		else
			seconds=0;
	}
}





