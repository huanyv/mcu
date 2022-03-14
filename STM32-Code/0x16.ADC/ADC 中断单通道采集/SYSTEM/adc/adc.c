#include "adc.h"

static void ADC_GPIO_Config(void) { // 配置ADC 的GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN; // 模拟输入
	GPIO_InitStructure.GPIO_Pin   = ADC_PIN; // ADC1通道0  即PA0口
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

static void ADC_MODE_Config(void) {  // 配置ADC模式
	ADC_InitTypeDef ADC_InitStructure; // ADC初始化结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE); // 使能ADC1的时钟 
	
	ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent; // 独立模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  // ADC连续转换
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None; // 关外部引脚触发，即 软件触发
	ADC_InitStructure.ADC_ScanConvMode       = DISABLE; // 工作在单通道模式
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right; // 数据采集向右对齐
	ADC_InitStructure.ADC_NbrOfChannel       = 1; // 1个采集通道
	ADC_Init(ADC1,&ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); // ADC时钟 8 分频  9Mhz
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5); // 常规通道配置
	
	ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE); // 使能ADC中断
	ADC_Cmd(ADC1,ENABLE);    //  使能ADC1 
	
	ADC_StartCalibration(ADC1);//开启ADC校准 
	while(ADC_GetCalibrationStatus(ADC1)); // 等待校准结束 
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE); // 使能ADC 软件 转换
}

static void ADC_NVIC_Config(void) {  // 配置中断优先级
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel                   = ADC1_2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_Init(&NVIC_InitStructure);
}
void ADC1_Init(void) {
	ADC_GPIO_Config();
	ADC_MODE_Config();
	ADC_NVIC_Config();
}

uint16_t ADC1_Channel_0_Value;

void ADC1_2_IRQHandler(void) {
	if(ADC_GetITStatus(ADC1,ADC_IT_EOC) == SET) { // 如果规则通道转换结束
		
		ADC1_Channel_0_Value = ADC_GetConversionValue(ADC1);    // ***取转换值 
		
		ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);  // 清除规则通道中断 标志位
	}
}
















