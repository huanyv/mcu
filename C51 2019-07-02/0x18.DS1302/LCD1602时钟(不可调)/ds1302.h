#ifndef _DS1302_H_
#define _DS1302_H_

#include<reg52.h>
#include<intrins.h>

#ifndef uchar
#define uchar unsigned char 
#endif

#ifndef uint
#define uint unsigned int 
#endif

sbit SCLK=P3^6;
sbit IO=P3^4;
sbit CE=P3^5;

void ds1302write(uchar add,uchar dat);
uchar ds1302read(uchar add);
void ds1302_init();
void ds1302_read_time();

extern uchar time[];





#endif