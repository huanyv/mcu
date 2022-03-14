#ifndef __BEEP_H
#define __BEEP_H
#include "sys.h"

#define        BEEP_GPIO               GPIOB
#define        BEEP_PIN                GPIO_Pin_8
#define        BEEP_GPIO_CLK           RCC_APB2Periph_GPIOB

#define        BEEP                    PBout(8)


void BEEP_GPIO_Config(void);

#endif /* __BEEP_H */
