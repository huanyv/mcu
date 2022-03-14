 //  System   INCLUDE
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"
#include "dma.h"

//  Hardware  INCLUDE
#include "led.h"
#include "key.h"


int main(void) {
	float temp;
	Sys_Init();
	USART1_Init();
	ADCX_Init();
	DMA_Config();	
	while(1) {
		printf("  0x%X  ",ADC_Value);
		temp = ((float)ADC_Value/4096)*3.3;
		printf("%f\n",temp);
		
		delay_s(1);
		
	} 
}



