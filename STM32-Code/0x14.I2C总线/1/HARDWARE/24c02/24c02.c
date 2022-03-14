#include "24c02.h"
#include "i2c.h"


/*****************写数据*******************/
void Write_24C02Addr(uint8_t addr,uint8_t date)
{
	I2C_Start();
	I2C_Write_Byte(0xa0);
	I2C_Respons();
	I2C_Write_Byte(addr);
	I2C_Respons();
	I2C_Write_Byte(date);
	I2C_Respons();
	I2C_Stop();
}

/******************读数据*******************/
uint8_t Read_24C02Addr(uint8_t addr)
{
	uint8_t dat;
	I2C_Start();
	I2C_Write_Byte(0xa0);
	I2C_Respons();
	I2C_Write_Byte(addr);
	I2C_Respons();
	I2C_Start();
	I2C_Write_Byte(0xa1);
	I2C_Respons();
	dat=I2C_Read_Byte();
	I2C_Stop();
	return dat;
}

