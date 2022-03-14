#include"TIME.h"
#include"reg52.h"

unsigned int TIME_Count  = 0;
unsigned int _TIME_Flag = 0;
void TIME0_Init() {
	TMOD = 0x02;
	EA   = 1;
	ET0  = 1;
	TH0  = TL0 = 56;
	TR0  = 0;
}
void TIME0_Delay_ms(unsigned int Delay_Time) {
	TR0 = 1;
	while(_TIME_Flag != Delay_Time);
	_TIME_Flag = 0;
	TR0        = 0;
}
void TIME0() interrupt 1
{
	if(++TIME_Count == 5){
		_TIME_Flag++;
		
		TIME_Count = 0;
	}
}










