#include "stm32f10x.h"
#include "delay.h"
#include "timer.h"
#include "key.h"
#include "display.h"
int main(void) {
	TIM2_Init();
	Display_GPIO_Init();
	key_init();
	while(1) {
		display();
		KEY_Contrl();
	}
}
