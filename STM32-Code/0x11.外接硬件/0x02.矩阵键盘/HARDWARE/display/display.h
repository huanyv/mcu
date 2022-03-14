#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include "sys.h"

#define  A38  PBout(2)
#define  B38  PBout(3)
#define  C38  PBout(4)

void Display_GPIO_Init(void);
void display(void);
#endif
