#include<reg52.h>
typedef unsigned char uchar;
typedef unsigned int uint;

#define wei P2

//uchar code duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uchar code duanxuan[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8, 
0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
void delay(uint iii)
{
	while(iii--);
}
/*
void weixuan()//����
{
	uchar i=1;			//0xef   4��
	for(wei=0xfe;wei!=0xff;wei=(wei<<1)|0x01)
	{
		P0=duanxuan[i++];
		if(i==9)i=1;
		delay(100);
		P0=0x00;
	}
}*/

void weixuan()//����
{
	uchar i=1;			//0x10   4��
	for(wei=0x01;wei!=0x00;wei=wei<<1|0x00)
	{
		P0=duanxuan[i++];
		if(i==9)i=1;
		delay(100);
		P0=0xff;
	}
}

void main()
{
	while(1)
	{
		weixuan();
	}
}