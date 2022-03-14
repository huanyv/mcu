#include "stm32f10x.h"
#include "display.h"
#include "delay.h"
int main(void) {
	Display_Init();
	while(1) {
		display();
	}
}




