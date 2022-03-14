#include "dma.h"


const uint32_t aSRC_Const_Buffer[DATA_COUNT]= {
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};
//定义DMA传输目标存储器
//存储在内部的SRAM中																		

uint32_t aDST_Buffer[DATA_COUNT];

//typedef struct
//{
//  uint32_t DMA_PeripheralBaseAddr;   // 外设地址
//  uint32_t DMA_MemoryBaseAddr;       // 存储器地址
//  uint32_t DMA_DIR;                  // 传输方向
//  uint32_t DMA_BufferSize;           // 传输数目
//  uint32_t DMA_PeripheralInc;        // 外设地址增量模式
//  uint32_t DMA_MemoryInc;            // 存储器地址增量模式
//  uint32_t DMA_PeripheralDataSize;   // 外设数据宽度
//  uint32_t DMA_MemoryDataSize;       // 存储器数据宽度
//  uint32_t DMA_Mode;                 // 模式选择
//  uint32_t DMA_Priority;             // 通道优先级
//  uint32_t DMA_M2M;                  // 存储器到存储器模式
//}DMA_InitTypeDef;

void DMA1_Config(void) {
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)aSRC_Const_Buffer;//外设地址
	DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)aDST_Buffer;  // DMA 存储器地址
	DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC; // 外设作为数据传输的来源
	DMA_InitStructure.DMA_BufferSize         = DATA_COUNT; // 传输个数 32 个
	DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal; // 工作在正常缓存模式
	DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Word;	// 数据的宽度 32 位
	DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;	// 内存地址递增使能
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; // 外设数据宽度 32 位
	DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Enable;	// 外设地址递增使能
	DMA_InitStructure.DMA_M2M                = DMA_M2M_Enable; // 内存到内存输出 
	DMA_InitStructure.DMA_Priority           = DMA_Priority_High;	// 设置为高优先级
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	
	DMA_ClearFlag(DMA1_FLAG_TC1); // 清除标志位
	
	DMA_Cmd(DMA1_Channel1,ENABLE); // 使能DMA
}

/*

DMA1_FLAG_GLx 通道 x 全局中断
DMA1_FLAG_TCx 通道 x 传输完成中断
DMA1_FLAG_HTx 通道 x 传输过半中断
DMA1_FLAG_TEx 通道 x 错误中断

*/


uint8_t Check_Data(void) {
	uint8_t i;
	for(i=0;i<DATA_COUNT;i++) {
		
		if(aSRC_Const_Buffer[i] != aDST_Buffer[i]) {
		
			return 0;
			
		}
	
	}
	
	return 1;
	
}














