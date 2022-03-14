#ifndef __ADC_H
#define __ADC_H
#include "sys.h"

#define           ADC_1                      ADC1
#define           ADC_PERIPH_CLK_CMD         RCC_APB2Periph_ADC1
#define           ADC_1_CHANNEL              ADC_Channel_16 // 通道 16 外接温度传感器
#define           ADC_1_ITCHANNEL            ADC1_2_IRQn



void ADCX_MODE_Config(void);

#endif /* __ADC_H */
