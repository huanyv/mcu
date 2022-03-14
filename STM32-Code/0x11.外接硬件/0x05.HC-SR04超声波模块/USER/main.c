#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "hcsr04.h"
#include "lcd1602.h"
uint16_t distance = 0;
uint16_t FLAG = 0;

void display(void) {
		if(distance < 450){
			LCD_Write_Cmd(0x80+5);
			if(distance>=100)
				LCD_Write_Dat((distance/100)+48);
			else 
				LCD_Write_Dat(' ');
			if(distance>=10)
				LCD_Write_Dat((distance/10%10)+48);
			else 
				LCD_Write_Dat(' ');
			LCD_Write_Dat((distance%10)+48);
			LCD_Write_Dat('C');
			LCD_Write_Dat('M');
		}
		else{
			LCD_Write_Cmd(0x80+5);
			LCD_Write_Dat('E');
			LCD_Write_Dat('R');
			LCD_Write_Dat('R');
			LCD_Write_Dat('O');
			LCD_Write_Dat('R');
		}
		if(FLAG == 0) {
			FLAG = 1;
			distance = HC_SR04ReadDistance();
		}
}

int main(void) {
	
	HC_SR04_GPIO_Init();
	LCD_Init();
	TIM2_Init(65535,71);
	TIM3_Init(7499,7199);
	while(1) {
		display();
	}
}
void TIM3_IRQHandler(void) {
	FLAG = 0;
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}












