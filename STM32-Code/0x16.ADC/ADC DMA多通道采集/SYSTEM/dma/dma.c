#include "dma.h"

uint16_t ADC_Value_ARRAY[ARRAY_NUMBER];

void DMA_Config(void) {
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)PERIPH_BASE_ADDR;
	DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)ADC_Value_ARRAY;
	DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
	DMA_InitStructure.DMA_BufferSize         = ARRAY_NUMBER;
	DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
	DMA_Init(DMAx_CHANNEL,&DMA_InitStructure);
	
	DMA_ClearFlag(DMA1_FLAG_TC1);
	DMA_Cmd(DMAx_CHANNEL,ENABLE);
}








