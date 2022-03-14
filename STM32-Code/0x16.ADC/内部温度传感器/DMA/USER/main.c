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

extern uint16_t temp_value;



int main(void) {
	float temp;
	Sys_Init();
	USARTx_Init();
	ADCX_MODE_Config();
	DMAX_Init();
	LED_GPIO_Config();
	
	while(1) {
		
		temp = (1.43-(3.3*((float)temp_value/4096)))/4.3+25;
		
		
		printf("ADÖµ£º%d\n",temp_value);
		printf("ÎÂ¶È£º%.2f\n\n\n",temp);
		
		
		
		
		LED0 = !LED0;
		delay_s(1);		
		
	} 
}
























