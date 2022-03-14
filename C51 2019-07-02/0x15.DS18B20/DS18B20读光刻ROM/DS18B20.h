#ifndef _DS18B20_H_
#define _DS18B20_H_

#include<reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

sbit DQ=P3^7;
void delay(uint i);
void DS18B20_init();
uchar DS18B20_read();
void DS18B20_write(uchar dat);
int readc();



#endif