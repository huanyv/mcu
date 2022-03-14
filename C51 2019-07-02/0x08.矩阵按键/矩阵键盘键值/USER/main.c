#include"reg52.h"
typedef unsigned char uchar;
typedef unsigned int uint;

sbit A38=P2^2;
sbit B38=P2^3;
sbit C38=P2^4;

#define BUTTON P1
#define countplay P0

uchar code duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
					 0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

uchar weizhi=0;
uchar count=0;

void key()
{
	uchar dat=0;//读 键值 变量
	static bit flag_song=0;//检测松手标志位
	static uint flag_delay=0;//检测消抖标志位
	BUTTON=0xf0;
	if(flag_song==0&&BUTTON!=0xf0)
	{
		flag_delay++;//消抖
		
		if(flag_delay>700&&BUTTON!=0xf0)
		{
			flag_delay=0;
			flag_song=1;
			
			dat=BUTTON;
			BUTTON=0x0f;
			dat=dat|BUTTON;
			switch(dat)
			{
				case 0x77:weizhi=1;break;
				case 0x7b:weizhi=2;break;
				case 0x7d:weizhi=3;break;
				case 0x7e:weizhi=4;break;

				case 0xb7:weizhi=5;break;
				case 0xbb:weizhi=6;break;
				case 0xbd:weizhi=7;break;
				case 0xbe:weizhi=8;break;

				case 0xd7:weizhi=9;break;
				case 0xdb:weizhi=10;break;
				case 0xdd:weizhi=11;break;
				case 0xde:weizhi=12;break;
				
				case 0xe7:weizhi=13;break;
				case 0xeb:weizhi=14;break;
				case 0xed:weizhi=15;break;
				case 0xee:weizhi=16;break;
			}
		}
	}
	if(BUTTON==0xf0)
	{
		flag_song=0;
		flag_delay=0;
	}
	if(weizhi==1)
	{
		weizhi=0;
		count++;
		if(count==10)count=0;
	}
}
void main()
{
	A38=0;
	B38=0;
	C38=0;
	while(1)
	{
		key();
		countplay=duanxuan[count];
	}
}













