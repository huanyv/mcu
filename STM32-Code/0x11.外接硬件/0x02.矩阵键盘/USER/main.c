#include "stm32f10x.h"

#include "delay.h"
#include "keyboard.h"
#include "display.h"
int main(void) {
  Display_GPIO_Init();
	while(1) {
		display();
	}
}





