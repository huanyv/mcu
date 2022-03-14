#ifndef __INFRARED_H
#define __INFRARED_H
#include "sys.h"
	
sbit IRIN=P3^2;


void Intrared_SPEED_Ctrl(void);
void Intrared_MODE_Ctrl(void);
void IrInit(void);
void ReadIr();

#endif /* __INFRARED_H */