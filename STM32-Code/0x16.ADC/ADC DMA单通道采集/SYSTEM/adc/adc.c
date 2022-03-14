#include "adc.h"

static void ADC_GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = ADC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ADC_GPIO,&GPIO_InitStructure);
}

static void ADC_MODE_Config(void) {
	ADC_InitTypeDef ADC_InitTypeStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	ADC_InitTypeStructure.ADC_Mode               = ADC_Mode_Independent; // ���� ADCģʽ
	ADC_InitTypeStructure.ADC_ScanConvMode       = DISABLE; // ɨ��ģʽ�ر�
	ADC_InitTypeStructure.ADC_ContinuousConvMode = ENABLE; // ����ת��
	ADC_InitTypeStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None; // �������ⲿӲ������
	ADC_InitTypeStructure.ADC_DataAlign          = ADC_DataAlign_Right; // �����������
	ADC_InitTypeStructure.ADC_NbrOfChannel       = 1; // 1��ͨ��
	ADC_Init(ADCX,&ADC_InitTypeStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); // ADCʱ�� 9 Mhz
	ADC_RegularChannelConfig(ADCX,ADC_Channel_0,1,ADC_SampleTime_55Cycles5); // ����ͨ������

	ADC_DMACmd(ADCX,ENABLE); // ʹ��ADC DMA
	ADC_Cmd(ADCX,ENABLE);
	
	ADC_StartCalibration(ADCX); // ��ʼУ׼ADC
	while( ADC_GetCalibrationStatus(ADCX) != RESET ); // �ȴ�У׼���
	
	ADC_SoftwareStartConvCmd(ADCX,ENABLE); // ʹ���������
}

void ADCX_Init(void) {
	ADC_GPIO_Config();
	ADC_MODE_Config();
}












