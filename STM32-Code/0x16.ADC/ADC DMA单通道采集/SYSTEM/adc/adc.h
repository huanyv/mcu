#ifndef __ADC_H
#define __ADC_H
#include "sys.h"

#define    ADC_PIN          GPIO_Pin_0
#define    ADC_GPIO         GPIOA

#define    ADCX             ADC1


void ADCX_Init(void);

#endif /* __ADC_H */
