#include<reg52.h>
typedef unsigned char uchar;
typedef unsigned int uint;

sbit LA=P2^2;
sbit LB=P2^3;
sbit LC=P2^4;

uchar code duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void yanshi(uint i)
{
	uint x,y;
	for(x=0;x<i;x++)
		for(y=0;y<60;y++);
}
void dontai()
{
	uint i;
	for(i=1;i<9;i++)
	{
		switch(i)
		{
			case 1:LC=0;LB=0;LA=0;break;
			case 2:LC=0;LB=0;LA=1;break;
			case 3:LC=0;LB=1;LA=0;break;
			case 4:LC=0;LB=1;LA=1;break;
			case 5:LC=1;LB=0;LA=0;break;
			case 6:LC=1;LB=0;LA=1;break;
			case 7:LC=1;LB=1;LA=0;break;
			case 8:LC=1;LB=1;LA=1;break;
		}
		P0=duanxuan[i];
		yanshi(1);
	//	P0=0x00;		  
	}
}
int main()
{
	while(1)
	{
		dontai();
	}
}