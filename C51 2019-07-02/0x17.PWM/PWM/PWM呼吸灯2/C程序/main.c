#include <REG52.H>

typedef unsigned char uchar;
typedef unsigned int uint;

//unsigned char PWM_COUNT; //计数
//unsigned int HUXI_COUNT;    //占空比更新时间
//unsigned char PWM_VLAUE;    //占空比比对值
//bit direc_flag;             //占空比更新方向

#define LED    P2

void timer0_init()
{
    TMOD=0x02;          //模式设置，00010000，定时器0，工作于模式2（M1=1，M0=0）
    TH0=256-100;               //定时器溢出值设置，每隔200us发起一次中断。
    TL0=256-100;
    TR0=1;                  //定时器0开始计时
    ET0=1;                  //开定时器0中断
    EA=1;                       //开总中断
//    PWM_COUNT =0;
}

void main()
{
//    HUXI_COUNT = 0;
//    PWM_COUNT = 0;
//    PWM_VLAUE = 0;
//    direc_flag = 0;
    LED = 1;            //默认LED熄灭   
    timer0_init();      //定时器0初始化
    while(1);
}
void time0() interrupt 1
{  
	static uchar PWM_COUNT=0; //计数
	static uint HUXI_COUNT=0;    //占空比更新时间
	static uchar PWM_VLAUE=0;    //占空比比对值
	static bit flag=0;  
    PWM_COUNT++;//中断次数，每中断一次+1,　　10 归零
    HUXI_COUNT++;
		if(PWM_COUNT == 10)PWM_COUNT = 0;
	
    if(PWM_COUNT < PWM_VLAUE)      //判断是否到了点亮LED的时候
        LED = 0XFF;                   
    else         //当前周期结束
        LED = 0X00;    
			
    if((HUXI_COUNT >= 700) && (flag == 0))
    {                               //占空比增加10%
        HUXI_COUNT = 0;
        PWM_VLAUE++;
        if(PWM_VLAUE >= 9)          //占空比更改方向
            flag = 1; 
    }
    if((HUXI_COUNT >= 700) && (flag == 1))
    {                               //占空比减少10%
        HUXI_COUNT = 0;
        PWM_VLAUE--;
        if(PWM_VLAUE <= 1)          //占空比更改方向
            flag = 0; 
    }   
}











