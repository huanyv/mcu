#include "adc.h"

static void ADC_GPIO_Config(void) { // ����ADC ��GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN; // ģ������
	GPIO_InitStructure.GPIO_Pin   = ADC_PIN; // ADC1ͨ��0  ��PA0��
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}

static void ADC_MODE_Config(void) {  // ����ADCģʽ
	ADC_InitTypeDef ADC_InitStructure; // ADC��ʼ���ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE); // ʹ��ADC1��ʱ�� 
	
	ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent; // ����ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  // ADC����ת��
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None; // ���ⲿ���Ŵ������� �������
	ADC_InitStructure.ADC_ScanConvMode       = DISABLE; // �����ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right; // ���ݲɼ����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel       = 1; // 1���ɼ�ͨ��
	ADC_Init(ADC1,&ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); // ADCʱ�� 8 ��Ƶ  9Mhz
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5); // ����ͨ������
	
	ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE); // ʹ��ADC�ж�
	ADC_Cmd(ADC1,ENABLE);    //  ʹ��ADC1 
	
	ADC_StartCalibration(ADC1);//����ADCУ׼ 
	while(ADC_GetCalibrationStatus(ADC1)); // �ȴ�У׼���� 
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE); // ʹ��ADC ��� ת��
}

static void ADC_NVIC_Config(void) {  // �����ж����ȼ�
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
	if(ADC_GetITStatus(ADC1,ADC_IT_EOC) == SET) { // �������ͨ��ת������
		
		ADC1_Channel_0_Value = ADC_GetConversionValue(ADC1);    // ***ȡת��ֵ 
		
		ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);  // �������ͨ���ж� ��־λ
	}
}
















