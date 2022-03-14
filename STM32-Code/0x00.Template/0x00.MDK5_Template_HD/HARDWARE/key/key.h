#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

/*
WK_UP --- PA0
KEY0  --- PE4
KEY1  --- PE3
KEY2  --- PE2
*/

#define         WKUP_ENABLE           0

#define         KEY_GPIO_CLK          RCC_APB2Periph_GPIOE
#define         KEY_GPIO              GPIOE
#define         KEY0_PIN              GPIO_Pin_4
#define         KEY1_PIN              GPIO_Pin_3
#define         KEY2_PIN              GPIO_Pin_2
#define         KEY_ALL_PIN           KEY0_PIN|KEY1_PIN|KEY2_PIN

// WK_UP
#define         KEY_WKUP_GPIO_CLK     RCC_APB2Periph_GPIOA
#define         KEY_WKUP_GPIO         GPIOA
#define         KEY_WKUP_PIN          GPIO_Pin_0


#define         KEY0                  PEin(4)
#define         KEY1                  PEin(3)
#define         KEY2                  PEin(2)
#define         WK_UP                 PAin(0)
								             



void KEY_GPIO_Config(void);

#endif /* __KEY_H */
