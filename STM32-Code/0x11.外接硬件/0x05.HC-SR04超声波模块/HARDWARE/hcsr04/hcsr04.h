#ifndef _HCSR04_H_
#define _HCSR04_H_
#include "sys.h"

#define    ECHO   PBout(1)
#define    TRIG   PBout(0)

void HC_SR04_GPIO_Init(void);
uint16_t HC_SR04ReadDistance(void);
#endif
