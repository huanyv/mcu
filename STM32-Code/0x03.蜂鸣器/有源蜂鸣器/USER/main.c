 //  System   INCLUDE
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"

//  Hardware  INCLUDE
#include "led.h"
#include "key.h"
#include "beep.h"



int main(void) {
	Sys_Init();
	USARTx_Init();
	BASIC_TIMX_Cofnig(624,57599);
	LED_GPIO_Config();
	BEEP_GPIO_Config();
	
	while(1) {		
		
		delay_ms(500);
		LED0 = !LED0;
		
	} 
}

void BASIC_TIMX_ITFUNCTION(void) {
	
	if( TIM_GetITStatus(BASIC_TIMX,TIM_IT_Update) != RESET )
	{
		
		BEEP = !BEEP;
		
		TIM_ClearITPendingBit(BASIC_TIMX,TIM_IT_Update);
	}
	
}


