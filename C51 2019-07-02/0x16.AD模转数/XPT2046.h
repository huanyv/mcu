#ifndef _XPT2046_H_
#define _XPT2046_H_

#include<reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif


sbit DCLK=P3^6;
sbit DIN=P3^4;
sbit CS=P3^5;
sbit DOUT=P3^7;


void write_date(uchar dat);
uint read_date();
uint xpt2046(uchar t);
void delay(uint i);

#endif