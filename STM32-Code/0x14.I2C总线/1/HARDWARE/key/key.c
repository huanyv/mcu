#include "key.h"
#include "delay.h"
#include "24c02.h"

uint8_t number = 0;

void GPIO_KEY_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	number = Read_24C02Addr(0x01);//读取E2PROM的数据
	if(number>100)number = 0;//以防读取错误数据
}

void KEY_Crtl(void) {
	static uint16_t KEY_Let_Go = 0;
	
	if((KEY1 == 0)&&(KEY_Let_Go == 0)) {
		delay_ms(10);
		if(KEY1 == 0) {
			
			KEY_Let_Go = 1;
			number++;
			if(number == 100)
				number = 0;
				Write_24C02Addr(0x01,number);//写入E2PROM
		}
	}
	if(KEY1 == 1)
		KEY_Let_Go = 0;
	
}
