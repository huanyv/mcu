#include "dma.h"

uint16_t temp_value;


void DMAX_Init(void) {
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(DMA_PERIPH_CLK_CMD,ENABLE);
	
	DMA_InitStructure.DMA_Mode                = DMA_Mode_Circular;
	DMA_InitStructure.DMA_BufferSize          = 1;
	DMA_InitStructure.DMA_DIR                 = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_PeripheralBaseAddr  = (uint32_t)PERIPH_ADC_1_BASE;
	DMA_InitStructure.DMA_MemoryBaseAddr      = (uint32_t)(&temp_value);
	DMA_InitStructure.DMA_PeripheralDataSize  = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize      = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc           = DMA_MemoryInc_Disable; // 不增量
	DMA_InitStructure.DMA_PeripheralInc       = DMA_PeripheralInc_Disable; // 不增量
	DMA_InitStructure.DMA_M2M                 = DMA_M2M_Disable;
	DMA_InitStructure.DMA_Priority            = DMA_Priority_High;
	DMA_Init(DMA_CHANNEL_1,&DMA_InitStructure);
	
	DMA_GetITStatus(DMA1_IT_TC1);
	
	DMA_Cmd(DMA_CHANNEL_1,ENABLE);	
}

