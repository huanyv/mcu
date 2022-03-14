#include "adc.h"

static void ADCX_NVIC_Config(void) {
	NVIC_InitTypeDef NVIC_InitSructure;
	NVIC_InitSructure.NVIC_IRQChannel                   = ADC_1_ITCHANNEL;
	NVIC_InitSructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_InitSructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitSructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_Init(&NVIC_InitSructure);
}
void ADCX_MODE_Config(void) {
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(ADC_PERIPH_CLK_CMD,ENABLE);
	ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode       = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel       = 1;
	ADC_Init(ADC_1,&ADC_InitStructure);	
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	ADC_RegularChannelConfig(ADC_1,ADC_1_CHANNEL,1,ADC_SampleTime_55Cycles5);
	
	ADC_Cmd(ADC_1,ENABLE);
	ADC_ITConfig(ADC_1,ADC_IT_EOC,ENABLE);	
	
	ADC_StartCalibration(ADC_1);
	while( ADC_GetCalibrationStatus(ADC_1) != RESET );
	
	ADC_SoftwareStartConvCmd(ADC_1,ENABLE);
	
	ADC_TempSensorVrefintCmd(ENABLE); // 使能温度位
	ADCX_NVIC_Config();
}
