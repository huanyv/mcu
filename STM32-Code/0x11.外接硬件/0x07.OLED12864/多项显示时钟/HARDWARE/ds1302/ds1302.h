#ifndef __DS1302_H
#define __DS1302_H
#include "sys.h"

#define   SCLK       PAout(14)
#define   IO         PAout(12)
#define   CE         PAout(13)

#define   IO_in      PAin(12)



#define   SCLK_PIN   GPIO_Pin_14
#define   IO_PIN     GPIO_Pin_12
#define   CE_PIN     GPIO_Pin_13

extern uint8_t time[];

void    GPIO_DS1302_Init(void);
uint8_t Read_DS1302(uint8_t addr);
void    Write_DS1302(uint8_t addr,uint8_t dat);
void    DS1302_Init(void);
void    DS1302_ReadTime(void);

#endif /* __DS1302_H */

