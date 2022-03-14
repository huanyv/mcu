#ifndef __DMA_H
#define __DMA_H
#include "sys.h"

#define    DATA_COUNT        32







extern uint32_t aDST_Buffer[DATA_COUNT];





void DMA1_Config(void);
uint8_t Check_Data(void);

#endif /* __DMA_H */
