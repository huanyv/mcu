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
	
	ADC_InitTypeStructure.ADC_Mode               = ADC_Mode_Independent; // 独立 ADC模式
	ADC_InitTypeStructure.ADC_ScanConvMode       = DISABLE; // 扫描模式关闭
	ADC_InitTypeStructure.ADC_ContinuousConvMode = ENABLE; // 连续转换
	ADC_InitTypeStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None; // 不采用外部硬件触发
	ADC_InitTypeStructure.ADC_DataAlign          = ADC_DataAlign_Right; // 数据右柔对齐
	ADC_InitTypeStructure.ADC_NbrOfChannel       = 1; // 1个通道
	ADC_Init(ADCX,&ADC_InitTypeStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); // ADC时钟 9 Mhz
	ADC_RegularChannelConfig(ADCX,ADC_Channel_0,1,ADC_SampleTime_55Cycles5); // 常规通道配置

	ADC_DMACmd(ADCX,ENABLE); // 使能ADC DMA
	ADC_Cmd(ADCX,ENABLE);
	
	ADC_StartCalibration(ADCX); // 开始校准ADC
	while( ADC_GetCalibrationStatus(ADCX) != RESET ); // 等待校准完成
	
	ADC_SoftwareStartConvCmd(ADCX,ENABLE); // 使能软件触发
}

void ADCX_Init(void) {
	ADC_GPIO_Config();
	ADC_MODE_Config();
}












