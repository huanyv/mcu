#include "dma.h"

uint8_t sendArray[ARRAY_NUMBER];

void DMA1_M_P_Config(void) {
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)PERIPH_BASE_Addr;
	DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)sendArray;
	DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_BufferSize         = ARRAY_NUMBER;
	DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel4,&DMA_InitStructure);
	
	DMA_ClearFlag(DMA1_FLAG_TC4);
	DMA_Cmd(DMA1_Channel4,ENABLE);	
}


