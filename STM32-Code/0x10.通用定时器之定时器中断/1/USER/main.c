#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "timer.h"

int main(void) {
	LED_init();
	TIM2_Init(4999,7199);    // (7200/72)*5000=500,000
	while(1);
}
