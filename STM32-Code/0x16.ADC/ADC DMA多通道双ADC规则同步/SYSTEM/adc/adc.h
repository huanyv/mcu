#ifndef __ADC_H
#define __ADC_H
#include "sys.h"

#define        ADC_GPIO                GPIOA
#define        ADC_PIN0                GPIO_Pin_0
#define        ADC_PIN1                GPIO_Pin_1
#define        ADC_PIN2                GPIO_Pin_2
#define        ADC_PIN3                GPIO_Pin_3
#define        ADC_ALL_PIN             ADC_PIN0|ADC_PIN1|ADC_PIN2|ADC_PIN3

#define        ADC_1                   ADC1
#define        ADC1_CHANNEL_0          ADC_Channel_0
#define        ADC1_CHANNEL_1          ADC_Channel_1
#define        ADC_2                   ADC2
#define        ADC2_CHANNEL_0          ADC_Channel_2
#define        ADC2_CHANNEL_1          ADC_Channel_3






void ADCX_Init(void);

#endif /*__ADC_H */
