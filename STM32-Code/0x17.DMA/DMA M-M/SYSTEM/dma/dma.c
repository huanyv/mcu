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
//����DMA����Ŀ��洢��
//�洢���ڲ���SRAM��																		

uint32_t aDST_Buffer[DATA_COUNT];

//typedef struct
//{
//  uint32_t DMA_PeripheralBaseAddr;   // �����ַ
//  uint32_t DMA_MemoryBaseAddr;       // �洢����ַ
//  uint32_t DMA_DIR;                  // ���䷽��
//  uint32_t DMA_BufferSize;           // ������Ŀ
//  uint32_t DMA_PeripheralInc;        // �����ַ����ģʽ
//  uint32_t DMA_MemoryInc;            // �洢����ַ����ģʽ
//  uint32_t DMA_PeripheralDataSize;   // �������ݿ��
//  uint32_t DMA_MemoryDataSize;       // �洢�����ݿ��
//  uint32_t DMA_Mode;                 // ģʽѡ��
//  uint32_t DMA_Priority;             // ͨ�����ȼ�
//  uint32_t DMA_M2M;                  // �洢�����洢��ģʽ
//}DMA_InitTypeDef;

void DMA1_Config(void) {
	DMA_InitTypeDef DMA_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)aSRC_Const_Buffer;//�����ַ
	DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)aDST_Buffer;  // DMA �洢����ַ
	DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC; // ������Ϊ���ݴ������Դ
	DMA_InitStructure.DMA_BufferSize         = DATA_COUNT; // ������� 32 ��
	DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal; // ��������������ģʽ
	DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Word;	// ���ݵĿ�� 32 λ
	DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;	// �ڴ��ַ����ʹ��
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; // �������ݿ�� 32 λ
	DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Enable;	// �����ַ����ʹ��
	DMA_InitStructure.DMA_M2M                = DMA_M2M_Enable; // �ڴ浽�ڴ���� 
	DMA_InitStructure.DMA_Priority           = DMA_Priority_High;	// ����Ϊ�����ȼ�
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	
	DMA_ClearFlag(DMA1_FLAG_TC1); // �����־λ
	
	DMA_Cmd(DMA1_Channel1,ENABLE); // ʹ��DMA
}

/*

DMA1_FLAG_GLx ͨ�� x ȫ���ж�
DMA1_FLAG_TCx ͨ�� x ��������ж�
DMA1_FLAG_HTx ͨ�� x ��������ж�
DMA1_FLAG_TEx ͨ�� x �����ж�

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














