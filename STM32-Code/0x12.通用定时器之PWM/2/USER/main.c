#include"pwm.h"
#include"delay.h"
#include"sys.h"
#include"key.h"
void KEY_CTRL(void) {
	static uint16_t  value = 10;
	static uint8_t   song = 0;
	if((GPIO_ReadInputDataBit(GPIOA,key1) == 0)&&(song == 0)) {
		delay_ms(10);
		if(GPIO_ReadInputDataBit(GPIOA,key1) == 0) {
			song = 1;
			value = value+30;
			TIM_SetCompare2(TIM3,value);
			if(value>100)value = 10;
		}
	}
	if(GPIO_ReadInputDataBit(GPIOA,key1) == 1) {
		song = 0;
	}
}

int main(void) {
	TIM3_PWM_Init(99,71);
	while(1) {
		KEY_CTRL();
		
	}
}









