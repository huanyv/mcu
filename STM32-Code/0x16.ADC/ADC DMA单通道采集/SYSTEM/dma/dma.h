#ifndef __DMA_H
#define __DMA_H
#include "sys.h"

#define    DMAx                DMA1
#define    DMAx_CHANNEL        DMA1_Channel1

#define    PERIPH_ADC_BASE     (ADC1_BASE+0x4C)


extern uint16_t ADC_Value;

void DMA_Config(void);

#endif /* __DMA_H */
