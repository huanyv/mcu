#ifndef _18B20_H_
#define _18B20_H_
#include "sys.h"

#define DQ   PAout(15)
int Read_Temp(void);
void GPIO_18B20_Init(void);
#endif
