#include "24c02.h"
#include "i2c.h"



void Write_24C02Addr(uint8_t addr,uint8_t dat)
{
	I2C_Start();
	I2C_Write_Byte(0xa0);
	I2C_Respons();
	I2C_Write_Byte(addr);
	I2C_Respons();
	I2C_Write_Byte(dat);
	I2C_Respons();
	I2C_Stop();
}


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



