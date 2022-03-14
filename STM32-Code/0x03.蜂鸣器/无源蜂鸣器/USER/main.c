#include"stm32f10x.h"
#include"buzzer.h"
#include"sys.h"
#include"delay.h"
int main(void){
	buzzer_init();
	delay_init();
	while(1){
		buzzer=0;
		delay_ms(1);
		buzzer=1;
		delay_ms(1);
	}
}
