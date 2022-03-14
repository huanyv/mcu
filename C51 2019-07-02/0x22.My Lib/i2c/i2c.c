#include "i2c.h"
#include <intrins.h>



#define     delay5us()      _nop_();_nop_();_nop_();_nop_();_nop_()


/***************��ʼ�ź�*************/
void I2C_Start(void)
{
	sda=1;
	delay5us();
	scl=1;
	delay5us();
	sda=0;
	delay5us();
	scl=0;
	delay5us();
}

/***************ֹͣ�ź�*************/
void I2C_Stop(void)
{
	sda=0;
	delay5us();
	scl=1;
	delay5us();
	sda=1;
	delay5us();
}

/**************Ӧ���ź�*************/
void I2C_Respons(void)
{
	uchar i;
	scl=1;
	delay5us();
	while((sda==1)&&(i<255))
		i++;
	scl=0;
	delay5us();
}

/**************��ʼ��*************/
void I2C_Init(void)
{
	sda=1;
	delay5us();
	scl=1;
	delay5us();
}

/***************дһ���ֽ�**********/
void Write_Byte(uchar date)
{
	uchar i,t;
	t=date;
	for(i=0;i<8;i++)
	{
		t=t<<1;
		scl=0;
		delay5us();
		sda=CY;
		delay5us();
		scl=1;
		delay5us();
	}
	scl=0;
	delay5us();
	sda=1;
	delay5us();
}

/***************��һ���ֽ�************/
uchar Read_byte()
{
	uchar i,k;
	scl=0;
	delay5us();
	sda=1;
   	delay5us();
	for(i=0;i<8;i++)
	{
		scl=1;
		delay5us();
		k=(k<<1)|sda;
		scl=0;
		delay5us();
	}
	return k;
}


/****************24c02*********************/
/*****************д����*******************/
void Write_Addr(uchar addr,uchar date)
{
	I2C_Start();
	Write_Byte(0xa0);
	I2C_Respons();
	Write_Byte(addr);
	I2C_Respons();
	Write_Byte(date);
	I2C_Respons();
	I2C_Stop();
}

/******************������*******************/
uchar Read_Addr(uchar addr)
{
	uchar date;
	I2C_Start();
	Write_Byte(0xa0);
	I2C_Respons();
	Write_Byte(addr);
	I2C_Respons();
	I2C_Start();
	Write_Byte(0xa1);
	I2C_Respons();
	date=Read_byte();
	I2C_Stop();
	return date;
}