 //  System   INCLUDE
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "dma.h"
#include "adc.h"

//  Hardware  INCLUDE
#include "led.h"
#include "key.h"

extern uint32_t ADC_VALUE_ARRAY[2];


int main(void) {
	uint16_t temp0,temp1;
	uint16_t temp2,temp3;
	float value[4];
	Sys_Init();
	USARTx_Init();
	DMA_Config();
	ADCX_Init();
	while(1) {
		
		temp0 = (ADC_VALUE_ARRAY[0]&0x0000FFFF);
		temp1 = (ADC_VALUE_ARRAY[0]&0xFFFF0000)>>16;
		temp2 = (ADC_VALUE_ARRAY[1]&0x0000FFFF);
		temp3 = (ADC_VALUE_ARRAY[1]&0xFFFF0000)>>16;
		value[0] = (float)temp0/4096*3.3;
		value[1] = (float)temp1/4096*3.3;
		value[2] = (float)temp2/4096*3.3;
		value[3] = (float)temp3/4096*3.3;
		
		printf("ADC1_CHANNL1:%f\n",value[0]);
		printf("ADC1_CHANNL2:%f\n",value[2]);
		printf("ADC2_CHANNL1:%f\n",value[1]);
		printf("ADC2_CHANNL2:%f\n",value[3]);
		printf("\n\n");
		delay_s(2);
		
	} 
}



