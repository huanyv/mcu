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

void delay_ds18b20(uint iii);
void ds18b20_init();
uchar ds18b20_read();
void ds18b20_write(uchar dat);
int ds18b20_read_temp();



#endif