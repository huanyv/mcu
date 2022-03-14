#ifndef _BULING_H_
#define _BULING_H_

#include<reg52.h>

		 #ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned int
#endif

sbit speaker = P1^5;

void song();

extern unsigned char timer0h, timer0l, time02;
extern code unsigned char sszymmh[];
extern code unsigned char FREQH[];
extern code unsigned char FREQL[];
#endif