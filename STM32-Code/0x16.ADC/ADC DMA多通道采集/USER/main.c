 //  System   INCLUDE
#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "dma.h"
#include "adc.h"

//  Hardware  INCLUDE
#include "led.h"
#include "key.h"


int main(void) {
	Sys_Init();
	USARTx_Init();
	ADCX_Init();
	DMA_Config();
	while(1) {
		
		printf("0x%X   ",ADC_Value_ARRAY[0]);
		printf("%f\n",((float)ADC_Value_ARRAY[0]/4096)*3.3);
		
		printf("0x%X   ",ADC_Value_ARRAY[1]);
		printf("%f\n",((float)ADC_Value_ARRAY[1]/4096)*3.3);
		
		printf("0x%X   ",ADC_Value_ARRAY[2]);
		printf("%f\n",((float)ADC_Value_ARRAY[2]/4096)*3.3);
		
		printf("0x%X   ",ADC_Value_ARRAY[3]);
		printf("%f\n",((float)ADC_Value_ARRAY[3]/4096)*3.3);
		
		printf("0x%X   ",ADC_Value_ARRAY[4]);
		printf("%f\n\n\n",((float)ADC_Value_ARRAY[4]/4096)*3.3);		
		
		delay_s(2);
		
	} 
}



