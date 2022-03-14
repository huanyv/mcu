#include "adc.h"

static void ADC_GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin  = ADC_ALL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ADC_GPIO,&GPIO_InitStructure);
}

static void ADC_MDOE_Config(void) {
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_ADC2,ENABLE);
	
	ADC_InitStructure.ADC_Mode               = ADC_Mode_RegSimult;
	ADC_InitStructure.ADC_ScanConvMode       = ENABLE; // 多个通道 要用连续转换
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_NbrOfChannel       = 2;
	ADC_Init(ADC_1,&ADC_InitStructure);
	
	ADC_InitStructure.ADC_Mode               = ADC_Mode_RegSimult;
	ADC_InitStructure.ADC_ScanConvMode       = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_NbrOfChannel       = 2;
	ADC_Init(ADC_2,&ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	ADC_RegularChannelConfig(ADC_1,ADC1_CHANNEL_0,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_1,ADC1_CHANNEL_1,2,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_2,ADC2_CHANNEL_0,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC_2,ADC2_CHANNEL_1,2,ADC_SampleTime_55Cycles5);
	
	ADC_DMACmd(ADC_1,ENABLE); // 开启ADC的DMA
	
	ADC_Cmd(ADC_1,ENABLE);
	ADC_ResetCalibration(ADC_1);
	while( ADC_GetResetCalibrationStatus(ADC_1) != RESET );
	ADC_StartCalibration(ADC_1);
	while( ADC_GetCalibrationStatus(ADC_1) != RESET );
	
	ADC_Cmd(ADC_2,ENABLE);
	ADC_ResetCalibration(ADC_2);
	while( ADC_GetResetCalibrationStatus(ADC_2) != RESET );
	ADC_StartCalibration(ADC_2);
	while( ADC_GetCalibrationStatus(ADC_2) != RESET );

  ADC_ExternalTrigConvCmd(ADC_2, ENABLE); // ADC2无法用DMA，外部控制使能
	ADC_SoftwareStartConvCmd(ADC_1, ENABLE); // 
}

void ADCX_Init(void) {
	ADC_GPIO_Config();
	ADC_MDOE_Config();
}












