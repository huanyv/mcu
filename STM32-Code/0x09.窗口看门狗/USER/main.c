#include"stm32f10x.h"
#include"led.h"
#include"delay.h"
#include"wwdg.h"
int main(void) {
	LED_init();
	WWDG_Init();
	
	while(1) {
		GPIO_SetBits(GPIOB,LED);//Œππ∑≥…π¶£¨‘Ú µ∆ …¡À∏
		delay_ms(500);
		GPIO_ResetBits(GPIOB,LED);
		delay_ms(500);
	}
}
