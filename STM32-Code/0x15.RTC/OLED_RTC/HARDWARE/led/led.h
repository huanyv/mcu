#ifndef __LED_H
#define __LED_H
#include "sys.h"

/*
LED0   PB5
LED1   PE5
*/

#define           LED_GPIO_CLK                     RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE
#define           LED0_GPIO                        GPIOB
#define           LED0_PIN                         GPIO_Pin_5
						    											             
#define           LED1_GPIO                        GPIOE
#define           LED1_PIN                         GPIO_Pin_5
						    											             
						    											             
						    											             
#define           LED0                             PBout(5)
#define           LED1                             PEout(5)



void LED_GPIO_Config(void);

#endif /* __LED_H */
