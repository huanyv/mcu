#include "key.h"
#include "delay.h"
#include "oled_i2c.h"
#include "i2c.h"
#include "24c02.h"

uint16_t count = 0;

void GPIO_KEY_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	count = (Read_24C02Addr(0x00)*256+Read_24C02Addr(0x01));
	if(count >= 65535)
		count = 0;
}

void KEY_Ctrl(void) {
	static uint8_t KEY_LET_GO = 0;
	
	if((KEY1 == 0)&&(KEY_LET_GO == 0)) {
		delay_ms(10);
			if(KEY1 == 0) {
				KEY_LET_GO = 1;
				
				count++;
				if(count > 65535)
					count = 0;
				Write_24C02Addr(0x00,((count&0xFF00)>>8));
				delay_ms(6);
				Write_24C02Addr(0x01,(count&0x00FF));

			}
	}
	if(KEY1 == 1) {
		KEY_LET_GO = 0;
	}
}

