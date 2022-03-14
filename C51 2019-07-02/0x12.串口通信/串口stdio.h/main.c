#include"reg52.h"
#include"intrins.h"
#include"stdio.h"

#define uint unsigned int 
#define uchar unsigned char

void uart(void)					//串口通信初始化
{
//	SCON=0x40;					//串口通信工作方式1
//	REN=1;						//允许接收
//	TMOD=0x20;					//定时器1的工作方式2
//	TH1=0xf3,TL1=0xf3;		
//	TI=1;                       //这里一定要注意
//	TR1=1;						//打开定时器
	SCON=0X50;			//设置为工作方式1
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍
	TH1=0XF3;				//计数器初始值设置，注意波特率是4800的
	TL1=0XF3;
	TI = 1;
	ES=1;						//打开接收中断
	EA=1;						//打开总中断
	TR1=1;
}								
void main(void)
{
	uint up=0,down=0,high=0;
	uint result ;
	uart();
	while(1)
		{ 	
			printf("********************************\r\n");
			printf("Please input up,dowm,high:\r\n");
			scanf("%d%d%d",&up,&down,&high)	;
			printf("\r\nResult=%d\r\n",result=(up+down)*high/2);
		}
}