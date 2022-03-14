#ifndef __DS18B20_H
#define __DS18B20_H
#include "sys.h"

sbit DQ=P1^5;

void DS18B20_Init();
uchar DS18B20_read();
void DS18B20_write(uchar dat);
uint readc();

#endif /* __DS18B20_H */