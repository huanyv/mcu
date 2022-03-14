#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit LA=P2^2;
sbit LB=P2^3;
sbit LC=P2^4;

#define duli P1
#define shuma P0

uchar code duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
					 0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

uint weizhi;

void yanshi(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
	for(j=0;j<60;j++);
}

void saomiao()
{
	uint a=0;
	duli=0x0f;
	if(duli!=0x0f)
	{
		yanshi(20);
		switch(duli)
		{
			case 0x07:weizhi=1;break;
			case 0x0b:weizhi=2;break;
			case 0x0d:weizhi=3;break;
			case 0x0e:weizhi=4;break;	
		}
		duli=0xf0;
		switch(duli)
		{
			case 0x70:break;
			case 0xb0:weizhi=weizhi+4;break;
			case 0xd0:weizhi=weizhi+8;break;
			case 0xe0:weizhi=weizhi+12;break;
		}
		while((a<50)&&(duli!=0xf0))
		{
			yanshi(20);
			a++;
		}
	}
}
int main()
{
	LA=0;
	LB=0;
	LC=0;
	while(1)
	{
		saomiao();
		shuma=duanxuan[weizhi-1];
	}
	return 0;
}