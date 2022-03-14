#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include "sys.h"

#define A38   PBout(2)
#define B38   PBout(3)
#define C38   PBout(4)

void display(void);
void GPIO_Display_Init(void);

#endif
