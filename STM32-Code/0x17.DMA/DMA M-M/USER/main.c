 //  System   INCLUDE
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "dma.h"

//  Hardware  INCLUDE
#include "led.h"
#include "key.h"


int main(void) {
	uint8_t i;
	Sys_Init();
	DMA1_Config();
	LED_GPIO_Config();
	USART1_Init();
	
	while( DMA_GetFlagStatus(DMA1_FLAG_TC1) == 0 );
	
	if(Check_Data() == 1) {
		LED1 = 0;
	}
	else {
		LED2 = 0;
	}
	delay_s(5);
	for(i=0;i<DATA_COUNT;i++) {
		
		printf("0x%X  ",aDST_Buffer[i]);
		
	}
	while(1) {
		LED3 = !LED3;
		delay_ms(500);
	} 
}



