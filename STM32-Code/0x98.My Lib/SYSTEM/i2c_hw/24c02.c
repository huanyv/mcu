#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "i2c.h"
#include "delay.h"
#include <stdio.h>
 
/* 从AT24CXX的指定地址开始读出一个字节 */
uint8_t AT24CXX_ReadByte(uint8_t ReadAddr)
{
	return I2C2_ReadByte(0xA0, ReadAddr);
}  
 
/* 向AT24CXX的指定地址开始写入一个字节 */
void AT24CXX_WriteByte(uint8_t WriteAddr, uint8_t Data)
{
	I2C2_WriteByte(0xA0, WriteAddr, Data);
}
 
void AT24CXX_test(void)
{
	uint8_t i;
   	I2C_InitTypeDef I2C_InitStructure; 
 
	I2C_InitStructure.I2C_ClockSpeed 	=  200000;	   //200kHZ
   	I2C_InitStructure.I2C_Mode 			=  I2C_Mode_I2C;
   	I2C_InitStructure.I2C_DutyCycle 	=  I2C_DutyCycle_2;	//根据datasheet，Tlow/Thigh = 2
   	I2C_InitStructure.I2C_OwnAddress1 	=  0xA0; 		
   	I2C_InitStructure.I2C_Ack 		 	=  I2C_Ack_Enable;
   	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	
	I2C2_Init(&I2C_InitStructure);
 
	for(i = 0; i < 10; i++){	
		AT24CXX_WriteByte(i, 100 + i);
		/* NOTE: 根据datasheet，两次字节写之间必须延迟5ms，也就是stop和start之间的间隔时间*/
		delay_ms(6);  
	}
	printf("Write completed \r\n");
 
	for(i = 0; i < 10; i++){	
		printf("%d ", AT24CXX_ReadByte(i));
	    delay_ms(6);
	}
	printf("\r\n");
}