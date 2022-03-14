#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include "sys.h"

#define C38  PBout(4)
#define B38  PBout(3)
#define A38  PBout(2)

void Display_Init(void);
void display(void);
#endif
