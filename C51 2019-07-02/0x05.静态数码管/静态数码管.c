#include<reg52.h>
typedef unsigned char uchar;
typedef unsigned int uint;
sbit LA=P2^2;
sbit LB=P2^3;
sbit LC=P2^4;
uchar code duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
					 0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};   //共阴数码管 段选  码表
void yanshi(uint j)
{	uint x,y;
	for(x=0;x<j;x++)
		for(y=0;y<60;y++);
}
int main()
{
	 int i;
	 LA=0;
	 LB=0;
	 LC=0;
	 while(1)
	 {
		 for(i=0;i<16;i++)
		 {
		 	P0=duanxuan[i];
		 	yanshi(1000);
		 }
	 }

	 return 0;
}