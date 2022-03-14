#ifndef __DMA_H
#define __DMA_H
#include "sys.h"


#define           DMA_CHANNEL_1                    DMA1_Channel1
#define           DMA_PERIPH_CLK_CMD               RCC_AHBPeriph_DMA1
#define           PERIPH_ADC_1_BASE                (ADC1_BASE+0X4C)








void DMAX_Init(void);

#endif /* __DMA_H */
