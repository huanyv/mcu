#ifndef _I2C_H_
#define _I2C_H_
#include "sys.h"

#define sda  PBout(0)
#define scl  PBout(1)

#define sda_in  PBin(0)
#define scl_in  PBin(1)

void    GPIO_I2C_Init(void);
void    I2C_Start(void);
void    I2C_Stop(void);
void    I2C_Respons(void);
void    I2C_Write_Byte(uint8_t dat);
uint8_t I2C_Read_Byte(void);



#endif 
