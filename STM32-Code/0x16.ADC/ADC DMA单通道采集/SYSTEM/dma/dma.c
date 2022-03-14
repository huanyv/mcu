#include "dma.h"

uint16_t ADC_Value = 0;

void DMA_Config(void) {
	DMA_InitTypeDef DMA_InitStucture;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitStucture.DMA_PeripheralBaseAddr = (uint32_t)PERIPH_ADC_BASE; // �����ַ�����ڵĽ��յ�ַ
	DMA_InitStucture.DMA_MemoryBaseAddr     = (uint32_t)( &ADC_Value); // ���� SRAM �ı��� ȡ��ַ
	DMA_InitStucture.DMA_DIR                = DMA_DIR_PeripheralSRC; // ������Ϊ����Դ
	DMA_InitStucture.DMA_BufferSize         = 1;  // 1�����ݳ���
	DMA_InitStucture.DMA_MemoryInc          = DMA_MemoryInc_Disable; // DMA �ڴ��ַ������
	DMA_InitStucture.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord; // �ڴ����� 16 λ
	DMA_InitStucture.DMA_PeripheralInc      = DMA_PeripheralInc_Disable; // �����ַ ������
	DMA_InitStucture.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // �������� 16 λ
	DMA_InitStucture.DMA_Mode               = DMA_Mode_Circular; // ѭ��ģʽ
	DMA_InitStucture.DMA_Priority           = DMA_Priority_High; // �����ȼ�
	DMA_InitStucture.DMA_M2M                = DMA_M2M_Disable; // �洢�����洢������ʧ��
	DMA_Init(DMAx_CHANNEL,&DMA_InitStucture);
	
	DMA_ClearFlag(DMA1_FLAG_TC1); // �����־λ
	
	DMA_Cmd(DMAx_CHANNEL,ENABLE);	// ʹ��ͨ��
}
