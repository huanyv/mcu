#include "reg52.h"
#include "lcd1602.h"
#include "hcsr04.h"

uint distance = 0;
bit read_flag = 1;

void TIM_Init(void)
{
	TMOD |= 0X11;
	TH0 = 0X00;
	TL0 = 0X00;
	TH1 = (65536-50000)/256;
	TL1 = (65536-50000)%256;
	ET1 = 1;
	TR1 = 1;
	
	EA  = 1;
}
void display(void) {
	if(distance<4500){
    LCD_write_0(0x80+4);
		LCD_write_1(distance/1000+'0');
    LCD_write_1(distance/100%10+'0');
    LCD_write_1(distance/10%10+'0');
		LCD_write_1('.');
    LCD_write_1(distance%10+'0');
    LCD_write_1('C');
    LCD_write_1('M');
	}
	else{
    LCD_write_0(0x80+4);
		LCD_write_1(' ');
		LCD_write_1('E');//ERROR
		LCD_write_1('R');
		LCD_write_1('R');
		LCD_write_1('O');
		LCD_write_1('R');
		LCD_write_1(' ');
	}
}
void main(void) {
		TIM_Init();
    LCD_Init();
    while(1) {
        display();
			if(read_flag == 1) {
					read_flag = 0 ;
					distance = HC_SR04EchoDistance();
			}
    }
}

void TIM1_Int() interrupt 3
{
	static uint i = 0;
	TH1 = (65536-50000)/256;
	TL1 = (65536-50000)%256;
	if(++i == 15) {
		i=0;
		read_flag = 1;
	}
}










