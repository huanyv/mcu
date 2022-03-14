#include "dma.h"

uint16_t ADC_Value = 0;

void DMA_Config(void) {
	DMA_InitTypeDef DMA_InitStucture;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitStucture.DMA_PeripheralBaseAddr = (uint32_t)PERIPH_ADC_BASE; // 外设地址，串口的接收地址
	DMA_InitStucture.DMA_MemoryBaseAddr     = (uint32_t)( &ADC_Value); // 存在 SRAM 的变量 取地址
	DMA_InitStucture.DMA_DIR                = DMA_DIR_PeripheralSRC; // 外设作为数据源
	DMA_InitStucture.DMA_BufferSize         = 1;  // 1个数据长度
	DMA_InitStucture.DMA_MemoryInc          = DMA_MemoryInc_Disable; // DMA 内存地址不增量
	DMA_InitStucture.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord; // 内存数据 16 位
	DMA_InitStucture.DMA_PeripheralInc      = DMA_PeripheralInc_Disable; // 外设地址 不增量
	DMA_InitStucture.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 外设数据 16 位
	DMA_InitStucture.DMA_Mode               = DMA_Mode_Circular; // 循环模式
	DMA_InitStucture.DMA_Priority           = DMA_Priority_High; // 高优先级
	DMA_InitStucture.DMA_M2M                = DMA_M2M_Disable; // 存储器到存储器传输失能
	DMA_Init(DMAx_CHANNEL,&DMA_InitStucture);
	
	DMA_ClearFlag(DMA1_FLAG_TC1); // 清除标志位
	
	DMA_Cmd(DMAx_CHANNEL,ENABLE);	// 使能通道
}
