#include <reg52.h>
sbit LED = P2^1;
unsigned char CYCLE;
unsigned char PWM_ON ;
void delay(unsigned int cnt)
{
	while(--cnt);
}
void main()
{
	bit Flag;
	TMOD |=0x01;
	TH0=(65536-100)/256;
	TL0=(65536-100)%256;
	IE= 0x82;
	TR0=1;
	CYCLE = 10;
	while(!Flag)//0
	{
		delay(6000);
		PWM_ON++;   
		if(PWM_ON == 10)
		{         
			Flag=1;
		}
	}
	while(Flag)//1
	{
		delay(6000);
		PWM_ON--;
		if(PWM_ON == 0)
		{
		  Flag=0;
		}
	}
}
void tim(void) interrupt 1 using 1
{
	static unsigned char count;
	TH0=(65536-100)/256;
	TL0=(65536-100)%256;
	if(count==PWM_ON)
	{
		LED = 1;  
	}
	count++;
	if(count == 10)
	{
	    count=0;
		if(PWM_ON!=0)
	    	LED = 0;
	}
}
/*
这个程序每一条语句你肯定能看懂，给你加注释没有必要，给你讲讲PWM的原理，你再对照程序看就明白了

你要用51产生PWM去控制LED，首先你要确定PWM的周期T和占空比D，确定了这些以后，
你可以用定时器产生一个时间基准t，比如定时器溢出n次的时间是PWM的高电平的时间，
则D*T=n*t，类似的可以求出PWM低电平时间需要多少个时间基准n'

那么你就可以编写程序，根据你定的时间基准 t 去给定时器赋值初始化，然后开启定时器，
定义一个标志位flag，根据flag的状态决定输出高平还是低电平，假设定义flag=1的时候输出高电平，
用一个变量去记录定时器中断的次数，每次中断就让记录中断次数的变量+1，在中断程序里面判断这个变量的值是否到了 n ,
如果到了说明高电平的时间够了，那么就改变flag为0，输出低电平，同时记录中断变量的值清零，
每次中断的时候依旧+1，根据flag=0的情况跳去判断记录变量的值是否到了 n' 如果到了，
说明PWM的低电平时间够了，那么就改flag=1，输出改高电平，同时记录次数变量清零，
重新开始，如此循环便可得到你想要的PWM波形。
*/
