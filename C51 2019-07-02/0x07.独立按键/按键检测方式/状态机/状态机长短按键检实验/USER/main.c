#include<reg52.h>

/*k1短按红灯亮，长按蓝灯亮*/

typedef unsigned char uchar;
typedef unsigned int uint;

sbit led_red=P0^2;
sbit led_blue=P0^0;
sbit k1=P3^1;

uchar readkey()
{
	static uchar keycount=0;
	static uint keytime=0;
	uchar key_return=0;
	switch(keycount)
	{
		case 0:
			if(k1==1)//没有按下
			{
				key_return=0;
			}
			else//按下
			{
				keycount=1;
				keytime=0;
			}break;		
		case 1:
			if(k1==0)
			{
				keytime++;
				if(keytime>=500)
				{
					keycount=2;
				}
			}
			else
			{
				keycount=0;
			}break;
		case 2:
			if(k1==1)
			{
				key_return=1;
				keycount=0;
			}
			else
			{
				keytime++;
				if(keytime>=10000)
				{
					key_return=11;
					keycount=3;
				}
			}break;
		case 3:
			if(k1==1)
			{
				keycount=0;
			}break;
	}
	return key_return;
}
void key()
{
	uchar key;
	key=readkey();
	if(key==1)
	{
		led_red=~led_red;
	}
	else if(key==11)
	{
		led_blue=~led_blue;
	}
}
void main(void)
{
	while(1)
	{
		key();
	}
}



























