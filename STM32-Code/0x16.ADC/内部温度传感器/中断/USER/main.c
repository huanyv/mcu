 //  System   INCLUDE
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"

//  Hardware  INCLUDE
#include "led.h"
#include "key.h"

uint16_t temp;


int main(void) {
	float tmp;
	Sys_Init();
	USARTx_Init();
	ADCX_MODE_Config();
	LED_GPIO_Config();
	
	while(1) {
		
		tmp = (1.43-((float)temp/4096)*3.3)/4.3;
		tmp = tmp+25;
		printf("%d\n",temp);
		printf("%.2f\n\n",tmp);		
		
		LED0 = !LED0;
		delay_s(1);
		
	} 
}

void ADC1_2_IRQHandler(void) {
	if( ADC_GetITStatus(ADC_1,ADC_IT_EOC) != RESET) {
		
		temp = ADC_GetConversionValue(ADC_1);
		
		ADC_ClearITPendingBit(ADC_1,ADC_IT_EOC);
	}
}


















