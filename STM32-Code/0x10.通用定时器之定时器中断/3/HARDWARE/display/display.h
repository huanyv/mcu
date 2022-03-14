#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include "sys.h"
#define C38    PBout(4)
#define B38    PBout(3)
#define A38    PBout(2)
void Display_GPIO_Init(void);
void display(void);


extern uint8_t sec;
extern uint8_t min;
extern uint8_t hour;
extern uint8_t year;
extern uint8_t month;
extern uint8_t day;
extern uint8_t date_flag;
#endif
