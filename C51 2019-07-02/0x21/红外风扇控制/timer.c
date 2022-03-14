#include "timer.h"


uint speed = 0;
bit TEMP_CAP = 0;

void TIM_Init(void) 
{
	TMOD = 0x11;
	
	TL0 = TLx;
	TH0 = THx;
	TL1 = (65536-50000)/256;
	TH1 = (65536-50000)%256;
	
	TR0 = 0; // 关闭定时器，电机默认停止状态
	ET0 = 0; // 关闭定时器中断，电机默认停止状态
	motor = 1;
	
	TR1 = 1;
	ET1 = 1;
	
	EA  = 1;
}	

void PWM_SPEED() interrupt 1
{
	static uint i = 0;
	TL0 = TLx;TH0 = THx;
	i++;
	if(i>10)
		i = 0;
	if(i<=speed)
		motor = 0;
	else
		motor = 1;
}
void TEMP_CAPTURE() interrupt 3
{
	static uchar i = 0;
	i++;
	if(i>19)
	{
		i = 0;
		TEMP_CAP = 1;
	}
}




