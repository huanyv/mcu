#ifndef _HCSR04_H_
#define _HCSR04_H_
#include "reg52.h"
#define  uint     unsigned int
#define  uchar    unsigned char
	
sbit TRIG = P2^0;
sbit ECHO = P2^1;

uint HC_SR04EchoDistance(void);


#endif
