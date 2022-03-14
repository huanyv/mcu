#include "adc.h"

static void ADCX_GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStrcture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStrcture.GPIO_Pin  = ADC_PIN0|ADC_PIN1|ADC_PIN2|ADC_PIN3|ADC_PIN4;
	GPIO_InitStrcture.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ADC_GPIO,&GPIO_InitStrcture);
}
static void ADCX_MODE_Config(void) {
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode       = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_NbrOfChannel       = 5;
	ADC_Init(ADCX,&ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	ADC_DMACmd(ADCX,ENABLE);
	ADC_Cmd(ADCX,ENABLE);
	
	ADC_RegularChannelConfig(ADCX,ADCX_CHANNEL_0,1,ADC_SampleTime_7Cycles5);
	ADC_RegularChannelConfig(ADCX,ADCX_CHANNEL_1,2,ADC_SampleTime_7Cycles5);
	ADC_RegularChannelConfig(ADCX,ADCX_CHANNEL_2,3,ADC_SampleTime_7Cycles5);
	ADC_RegularChannelConfig(ADCX,ADCX_CHANNEL_3,4,ADC_SampleTime_7Cycles5);
	ADC_RegularChannelConfig(ADCX,ADCX_CHANNEL_4,5,ADC_SampleTime_7Cycles5);
	
	ADC_StartCalibration(ADCX);
	while( ADC_GetCalibrationStatus(ADCX) == SET );
	ADC_SoftwareStartConvCmd(ADCX,ENABLE);
}

void ADCX_Init(void) {
	ADCX_GPIO_Config();
	ADCX_MODE_Config();
}








