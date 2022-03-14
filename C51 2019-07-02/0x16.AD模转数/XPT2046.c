#include<xpt2046.h>
#include<intrins.h>

void delay(uint i)
{
	while(i--);
}

void write_date(uchar dat)
{
	uchar i;
	DCLK=0;					 //��  ��ʼ  ��������  ǰ  Ӧ���ú�  ʱ����  ��  ��ʼ״̬
	for(i=0;i<8;i++)
	{
		DIN=dat>>7;
		dat=dat<<1;
		DCLK=0;			   // ʱ������   ������
		DCLK=1;			   // �ᷢ�� ��д��  ����
	}
}
uint read_date()
{
	uint i,dat=0;			//datҪ����ֵ    ÿ��ѭ����Ϊ  һ��ʼ  Ϊ   0
	DCLK=0;
	for(i=0;i<12;i++)
	{
		dat=dat<<1;
		DCLK=1;			 //		ʱ������  �½��� 
		DCLK=0;			 //		����� ������  ���� 
		dat=dat|DOUT;
	}
	return dat;	
}

uint xpt2046(uchar t)
{
	uint AD;
	DCLK=0;
	CS=0;	
	write_date(t);
//	delay(1);		 //��ʱ��Ҫ̫��
/*	DCLK=1;
	_nop_();
	_nop_();
	DCLK=0;
	_nop_();
	_nop_();          */	
	AD=read_date();
	CS=1;
	return AD;
}