#ifndef __DMA_H
#define __DMA_H
#include "sys.h"

#define      DMAx_CHANNEL           DMA1_Channel1
#define      PERIPH_BASE_ADDR      (ADC1_BASE+0x4C)

#define      ARRAY_COUNT           2



void DMA_Config(void);

#endif /* __DMA_H */
