 //  System   INCLUDE
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"

//  Hardware  INCLUDE
#include "led.h"
#include "key.h"




int main(void) {
	Sys_Init();
	USARTx_Init();
	LED_GPIO_Config();
	
	while(1) {
		
		//printf("666666\n\n");
		LED0 = !LED0;
		delay_ms(500);
		
	} 
}



