#ifndef __DMA_H
#define __DMA_H
#include "sys.h"

#define     ARRAY_NUMBER         5

#define     DMAx_CHANNEL          DMA1_Channel1
#define     PERIPH_BASE_ADDR     (ADC1_BASE+0x4C)



extern uint16_t ADC_Value_ARRAY[ARRAY_NUMBER];


void DMA_Config(void);

#endif /* __DMA_H */
