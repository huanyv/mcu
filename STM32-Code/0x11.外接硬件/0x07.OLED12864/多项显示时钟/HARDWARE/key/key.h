#ifndef _KEY_H_
#define _KEY_H_
#include "sys.h"

#define   KEY1        PAin(9)
#define   KEY2        PAin(10)
#define   KEY3        PAin(8)
#define   KEY4        PAin(11)  

#define   KEY1_PIN    GPIO_Pin_9
#define   KEY2_PIN    GPIO_Pin_10
#define   KEY3_PIN    GPIO_Pin_8
#define   KEY4_PIN    GPIO_Pin_11


#define   SETTING     KEY1 //设置键
#define   ADJUST      KEY2 //调整时间


void GPIO_KEY_Init(void);
void KEY_Crtl_display(void);
void INT_Init(void);

extern uint8_t  MENU1;
extern uint8_t  MENU2;

#endif
