#ifndef __DMA_H
#define __DMA_H
#include "sys.h"

#define    ARRAY_NUMBER              500
#define    PERIPH_BASE_Addr          (USART1_BASE+0x04)


extern uint8_t sendArray[ARRAY_NUMBER];

void DMA1_M_P_Config(void);

#endif /* __DMA_H */
