//  System
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"

//  Hardware  
#include "led.h"
#include "key.h"


extern uint16_t ADC1_Channel_0_Value; // ADC值

int main(void) {
	float temp = 0.0;
	Sys_Init();
	USART1_Init();
	ADC1_Init();
	while(1) {
		temp = ((float)ADC1_Channel_0_Value/4096)*3.3; // 电压转换
		printf("0x%X\n",ADC1_Channel_0_Value); // 打印 16 进制 结果
		printf("   %.2f\n",temp);  // 打印电压
		delay_ms(1000); // 减缓打印速度
		
	} 
}



