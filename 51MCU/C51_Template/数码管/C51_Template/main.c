
/*
	�����ѭ����ʾ 0 - 9
*/

#include"reg52.h"

#define uchar unsigned char
#define uint  unsigned int

sbit weixuan=P1^0; // λѡ 

uchar code duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
					 0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};   //��������� ��ѡ  ���

					 
void delay1ms(uint i)   //��� 0us
{
    unsigned char a,b,c;
	while(i--)
	{
	    for(c=1;c>0;c--)
	        for(b=142;b>0;b--)
	            for(a=2;a>0;a--);
	}
}
					 
					 

void main()
{
	uchar i;
	weixuan = 0;//���������  λѡ�� ��
	while(1)
	{
		for(i=0;i<10;i++)//ѭ�� 0-9
		{
			P0=duanxuan[i];
			delay1ms(1000);// 1000ms = 1s
		}
	}
	
}








