  //  System Include
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "i2c.h"

//  Hardware  Include
#include "led.h"
#include "key.h"
#include "dht11.h"
#include "oled_i2c.h"



int main(void) {

	Temperature_AND_Humidity Temperature_AND_humidity_Structure;
	DHT11_Init();
	GPIO_I2C_Init();
	OLED_Init();
	
	OLED_ShowCN(0,1,0);
	OLED_ShowCN(16,1,1);
	OLED_ShowStr(32,1,":",2);
	OLED_ShowCN(0,5,2);
	OLED_ShowCN(16,5,3);
	OLED_ShowStr(32,5,":",2);
	
	while(1) {
		
		Receive_DATA(&Temperature_AND_humidity_Structure);
		
		OLED_ShowStr(48,1,Temperature_AND_humidity_Structure.TEMP,2);
		OLED_ShowStr(48,5,Temperature_AND_humidity_Structure.HUM,2);
		
	} 
}



