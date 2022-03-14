#include "delay.h"
#include "sys.h"
#include "i2c.h"

#include "key.h"
#include "oled_i2c.h"
#include "18b20.h"
#include "ds1302.h"
#include "oled_display.h"



int main(void) {
	delay_Init();
	GPIO_I2C_Init();
	GPIO_18B20_Init();
	GPIO_DS1302_Init();
	
	DS1302_Init();
	OLED_Init();
	INT_Init();
	while(1) {
		
		display();
		KEY_Crtl_display();
		
	} 
}



