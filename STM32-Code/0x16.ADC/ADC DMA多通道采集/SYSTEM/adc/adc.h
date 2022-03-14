#ifndef __ADC_H
#define __ADC_H
#include "sys.h"

#define      ADC_GPIO             GPIOA
#define      ADC_PIN0             GPIO_Pin_0
#define      ADC_PIN1             GPIO_Pin_1
#define      ADC_PIN2             GPIO_Pin_2
#define      ADC_PIN3             GPIO_Pin_3
#define      ADC_PIN4             GPIO_Pin_4

#define      ADCX                 ADC1
#define      ADCX_CHANNEL_0       ADC_Channel_0
#define      ADCX_CHANNEL_1       ADC_Channel_1
#define      ADCX_CHANNEL_2       ADC_Channel_2
#define      ADCX_CHANNEL_3       ADC_Channel_3
#define      ADCX_CHANNEL_4       ADC_Channel_4




void ADCX_Init(void);

#endif /* __ADC_H */
