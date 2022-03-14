 //  System   INCLUDE
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"

//  Hardware  INCLUDE
#include "led.h"
#include "key.h"



#define      TRIG             PAout(1)
#define      ECHO             PAin(0)

void HC_SR04_GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
void HC_SR04_STATE(void) {
	TRIG = 1;
	delay_us(15);
	TRIG = 0;
}

int main(void) {
	float distance;
	Sys_Init();
	USARTx_Init();
	TIMX_Init(65535,71);
	LED_GPIO_Config();
	HC_SR04_GPIO_Config();
	while(1) {		
		
		HC_SR04_STATE();
		if( Capture_Structure.Capture_Okay_FLAG == 1 ) {
			
			distance = (float)((Capture_Structure.Capture_Count*65536)+Capture_Structure.Capture_Value)*0.017;
			
			if( distance<400 )
				printf("%.2fCM\n\n",distance);
			else
				printf("ERROR!\n\n");
			Capture_Structure.Capture_Okay_FLAG   = 0;
			Capture_Structure.Capture_Rising_FLAG = 0;
			
		}
		
		LED0 = !LED0;
		delay_ms(500);
		
	}
}








