#include"reg52.h"
#include"display.h"


void display()
{
	if(flag==1||flag==2)	//״̬1��״̬2���������ϱ���2��
	{
		bit_0=0;bit_1=1;
	
		P0=duanxuan[sec%10];
		delay(100);P0=0x00;
		if(sec>2)
		{
			P1=duanxuan[(sec-2)%10];
			delay(200);P1=0x00;
		}
		else
		{
			P1=duanxuan[sec%10];
			delay(200);P1=0x00;
		}
	
		bit_0=1;bit_1=0;
		
		P0=duanxuan[sec/10];
		delay(100);P0=0x00;
		if(sec>2)
		{
			P1=duanxuan[(sec-2)/10];
		    delay(200);P1=0x00;
		}
		else
		{
			P1=duanxuan[sec/10];
			delay(200);P1=0x00;
		} 
	}
	else if(flag==3||flag==4)//״̬3��״̬4���ϱ��ȶ�����2��
	{
		bit_0=0;bit_1=1;
	
		P1=duanxuan[sec%10];
		delay(100);P1=0x00;
		if(sec>2)
		{
			P0=duanxuan[(sec-2)%10];
			delay(200);P0=0x00;
		}
		else
		{
			P0=duanxuan[sec%10];
			delay(200);P0=0x00;
		}
	
		bit_0=1;bit_1=0;
		
		P1=duanxuan[sec/10];
		delay(100);P1=0x00;
		if(sec>2)
		{
			P0=duanxuan[(sec-2)/10];
		    delay(200);P0=0x00;
		}
		else
		{
			P0=duanxuan[sec/10];
			delay(200);P0=0x00;
		} 	
	}
	else if(flag==6||flag==7||flag==8)	 //·��ͨ�й���
	{
		bit_0=0;bit_1=1;

		P0=0x3f;
		delay(100);P0=0x00;
		P1=0x3f;
		delay(100);P1=0x00;

		bit_0=1;bit_1=0;

		P0=0x3f;
		delay(100);P0=0x00;
		P1=0x3f;
		delay(100);P1=0x00;
	}
}
