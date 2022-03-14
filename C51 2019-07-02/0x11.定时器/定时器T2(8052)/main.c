#include"stc89c5xrc.h"
typedef unsigned char uchar;
typedef unsigned int uint;

sbit A38=P2^2;
sbit B38=P2^3;
sbit C38=P2^4;

#define count 50000
#define THx (65536-count)/256;
#define TLx (65536-count)%256;

uchar sec=0;
uchar table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void timer2_init(void){
	EXEN2=0;//关闭T2EX的跳变
	C_T2=0;//使用定时器功能
	RCLK=TCLK=0;//
	TR2=1;//启动定时器
	EA=1;ET2=1;//打开中断

	RCAP2L=TL2=TLx;//低八位
	RCAP2H=TH2=THx;//高八位
}

void main(void){
	A38=0;
	B38=0;
	C38=0;
	timer2_init();
	while(1){
	
	
		P0=table[sec];
		
		
	}
}
void timer2() interrupt 5
{
	static uchar i=0;
	TF2=0;//软件 清 标志位
	if(++i==20)
	{
		i=0;
		sec++;
		if(sec==10)
		{
			sec=0;
		}
	}
}





















