#ifndef _USART_H_
#define _USART_H_
#include "stdio.h"	
#include "sys.h" 

void My_USART_Init(void);
int fputc(int ch, FILE *f);
int GetKey (void);


#endif


