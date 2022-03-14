#include<reg52.h>
typedef unsigned int uint;
typedef unsigned char uchar;

sbit k1=P3^1;
sbit LA=P2^2;
sbit LB=P2^3;
sbit LC=P2^4;

uchar code duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
					 0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};   //共阴数码管 段选  码表
					  
uint i=0;


//void yanshi(uint x)
//{
//	uint k,j;
//	for(k=0;k<x;k++)
//		for(j=0;j<60;j++);
//}
void display()
{
	LA=0;LB=0;LC=0;
	P0=duanxuan[i];
}
void key()
{
	static bit flag_song=0;
	static uint flag_delay=0;
	if(flag_song==0&&k1==0)
	{
		flag_delay++;
		if(flag_delay>=700&&k1==0)
		{
			flag_delay=0;
			flag_song=1;
			i++;
			if(i==10)i=0;
		}
	}
	if(k1==1)
	{
		flag_song=0;
		flag_delay=0;
	}
}
int main()
{	
	while(1)
	{
		display();
		key();
	}
	return 0;
}