#ifndef _IIC_H_
#define _IIC_H_
#include<reg52.h>


#define uchar unsigned char
#define uint unsigned int


sbit scl=P2^1;
sbit sda=P2^0;



void I2C_Start(void);
void I2C_Stop(void);
void I2C_Respons(void);
void I2C_Init(void);
void Write_Byte(uchar date);
uchar Read_byte();

 // 24c02
void Write_Addr(uchar addr,uchar date);
uchar Read_Addr(uchar addr);



#endif