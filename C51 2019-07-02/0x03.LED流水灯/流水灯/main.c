#include<reg52.h>
typedef unsigned char uchar;
typedef unsigned int uint;

#define led P2

void delay(uint iii)
{
	while(iii--);
}

//void led_ctrl()//Á÷Ë®µÆ
//{
//	for(led=0xfe;led!=0xff;led=(led<<1)|0x01)
//	{
//		delay(30000);
//	}
//	for(led=0xbf;led!=0xfe;led=(led>>1)|0x80)
//	{
//		delay(30000);
//	}
//}
//void led_ctrl()//ÖðÁÁÖðÃð
//{
//	for(led=0xff;led!=0x00;led=led>>1|0x00)//0111 1111           0011 1111
//	{
//		delay(30000);
//	}
//	for(led=0x00;led!=0xff;led=led<<1|0x01)
//	{
//		delay(30000);
//	}
//	for(led=0xff;led!=0x00;led=led<<1|0x00)
//	{
//		delay(30000);
//	}
//	for(led=0x00;led!=0xff;led=led<<1|0x01)
//	{
//		delay(30000);
//	}
//}

//void led_ctrl()
//{
//	uchar led1=0xe0,led2=0x07;
//	for(led=(led1|led2);led!=0xff;led=(led1<<1|0x10)|(led2>>1|0x08))
//	{
//		delay(30000);
//	}
//}

//void led_ctrl()
//{
//	for(led=0xe7;led!=0xff;led=((led/16)<<1|0x10)|((led%16)>>1|0x08))
//	{
//		delay(30000);
//	}
//}


void main()
{
	while(1)
	{
		led_ctrl();
	}
}

