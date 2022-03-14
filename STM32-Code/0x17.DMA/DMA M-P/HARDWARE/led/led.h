#ifndef _LED_H_
#define _LED_H_
#include "sys.h"


#define    LED1_PIN     GPIO_Pin_0
#define    LED2_PIN     GPIO_Pin_1
#define    LED1         PBout(0)
#define    LED2         PBout(1)



void LED_GPIO_Config(void);





#endif
