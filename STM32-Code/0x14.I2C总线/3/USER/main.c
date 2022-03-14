#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "i2c.h"
#include "oled_i2c.h"



int main(void) {
	GPIO_I2C_Init();
	OLED_Init();
	GPIO_KEY_Init();
	while(1) {
		
		
		KEY_Ctrl();
	
		OLED_Show16x32(0,0,count/10000);
		OLED_Show16x32(16,0,count/1000%10);
		OLED_Show16x32(32,0,count/100%10);
		OLED_Show16x32(48,0,count/10%10);
		OLED_Show16x32(64,0,count%10);
		
		
	} 
}



