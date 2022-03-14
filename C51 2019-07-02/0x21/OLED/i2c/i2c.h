#ifndef _IIC_H_
#define _IIC_H_
#include<reg52.h>


#define      uint8_t          unsigned char
#define      uint16_t         unsigned int
#define      OLED_ADDR        0x78

sbit scl=P2^1;
sbit sda=P2^0;



void I2C_Start(void);
void I2C_Stop(void);
void I2C_Respons(void);
void I2C_Init(void);
void I2C_Write_Byte(uint8_t date);
uint8_t I2C_Read_Byte(void);

 // 24c02
void Write_Addr(uint8_t addr,uint8_t date);
uint8_t Read_Addr(uint8_t addr);



#endif