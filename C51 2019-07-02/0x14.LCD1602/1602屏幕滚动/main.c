#include"reg52.h"
#include"lcd1602.h"

#define FOSC  12000000L
#define T20MS (65536-FOSC/12/1000)

uchar code table1[] = "xingtaizhiye";
uchar code table2[] = " liyaolong! ";

void Time_Init() {
	C_T2 = 0;
	TCLK = RCLK = 0;
	CP_RL2 = 0;
	RCAP2H = TH2 = T20MS>>8;
	RCAP2L = TL2 = T20MS;
	EA  = 1;
	ET2 = 1;
	TR2 = 1;
}
void main(void){
	uchar i = 0;
	LCD_init();
	Time_Init();
	for(i = 0;table1[i]!='\0';i++) {
		LCD_X_Y(1,i,table1[i]);
	}
	for(i = 0;table2[i]!='\0';i++) {
		LCD_X_Y(2,i,table2[i]);
	}
	while(1) {
		
	}
}
	
void  Timer2() interrupt 5 
{
	static unsigned int i = 0;
	TF2 = 0;
	if(++i == 500) {
		i = 0;
		LCD_write_0(0x1c);
	}
}








