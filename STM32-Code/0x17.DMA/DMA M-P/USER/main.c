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
	uint16_t i = 0;
	Sys_Init();
	LED_GPIO_Config();
	USART1_Init();
	DMA1_M_P_Config();
	
	for(i = 0;i < ARRAY_NUMBER;i++) {
		sendArray[i] = 'A';
	}
	
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); // Ê¹ÄÜ´®¿ÚDMA
	
	while(1) {
		LED1 = 0;
		LED2 = 1;
		delay_ms(500);
		LED1 = 1;
		LED2 = 0;
		delay_ms(500);
	} 
}





