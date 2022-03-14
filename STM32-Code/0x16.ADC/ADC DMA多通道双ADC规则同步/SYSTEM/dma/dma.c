#include "dma.h"

uint32_t ADC_VALUE_ARRAY[ARRAY_COUNT];

void DMA_Config(void) {
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)PERIPH_BASE_ADDR;
	DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)ADC_VALUE_ARRAY;
	DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
	
	DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable; // 存储地址自增
	DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Word; // ADC1的结果 + ADC2的结果，一共32位   
	DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	
	DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
	DMA_InitStructure.DMA_BufferSize         = ARRAY_COUNT;
	DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
	DMA_Init(DMAx_CHANNEL,&DMA_InitStructure); 
	
	DMA_ClearFlag(DMA1_FLAG_TC1);
	DMA_Cmd(DMAx_CHANNEL,ENABLE);
}

