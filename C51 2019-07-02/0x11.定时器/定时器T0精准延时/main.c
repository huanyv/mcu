#include"REG52.h"
#include"TIME.h"

sbit LED1 = P2^0;

void main(void) {
	TIME0_Init();
	while(1) {
		LED1 = ~LED1;
		TIME0_Delay_ms(500);
	}
}