#ifndef _KEY_H_
#define _KEY_H_
#include "sys.h"

#define   KEY1   PAin(9)

void GPIO_KEY_Init(void);
void KEY_Ctrl(void);

extern uint16_t count;

#endif
