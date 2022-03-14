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
	uint8_t i;
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
void I2C_Write_Byte(uint8_t date)
{
	uint8_t i,t;
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
//uint8_t I2C_Read_Byte(void)
//{
//	uint8_t i,k;
//	scl=0;
//	delay5us();
//	sda=1;
//   	delay5us();
//	for(i=0;i<8;i++)
//	{
//		scl=1;
//		delay5us();
//		k=(k<<1)|sda;
//		scl=0;
//		delay5us();
//	}
//	return k;
//}


























