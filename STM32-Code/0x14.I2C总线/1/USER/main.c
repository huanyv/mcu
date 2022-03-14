#include "stm32f10x.h"
#include "key.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "display.h"
#include "24c02.h"
#include "i2c.h"


int main(void) {
	GPIO_I2C_Init();
	GPIO_Display_Init();
	GPIO_KEY_Init();

	while(1) {
		display();
		KEY_Crtl();
	}
}

