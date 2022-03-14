 //  System   INCLUDE
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"

//  Hardware  INCLUDE
#include "led.h"
#include "key.h"




int main(void) {
	Sys_Init();
	USARTx_Init();
	TIMx_Init(65535,71);
	
	while(1) {
		
		if( CAPTURE_TypeDefStructure.Capture_Okay_FLAG == SET )
		{
			
			printf("%8.dus",CAPTURE_TypeDefStructure.Capture_Value+CAPTURE_TypeDefStructure.Capture_Count*65536);			
			
			printf("%5.2fs\n\n",(float)(CAPTURE_TypeDefStructure.Capture_Value+CAPTURE_TypeDefStructure.Capture_Count*65536)/1000000);
			
			
			CAPTURE_TypeDefStructure.Capture_Rising_FLAG = 0;
			CAPTURE_TypeDefStructure.Capture_Okay_FLAG  = 0;
		}
		
	} 
	
}



