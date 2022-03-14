#include <reg52.h>
#include "i2c.h"
#include "oled.h"



int main(void) {
	I2C_Init();
	OLED_Init();
	while(1) {
		
		
		Showstr8x16(0,0,"0123456789");

		
	}
	
}











