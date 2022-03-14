#include "adc.h"



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
	ADC_DMACmd(ADC_1,ENABLE);
	
	ADC_Cmd(ADC_1,ENABLE);
	
	ADC_StartCalibration(ADC_1);
	while( ADC_GetCalibrationStatus(ADC_1) != RESET );
	
	ADC_SoftwareStartConvCmd(ADC_1,ENABLE);
	ADC_TempSensorVrefintCmd(ENABLE);
}

