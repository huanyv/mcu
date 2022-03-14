#if 0

#include <REG52.H>

typedef unsigned char uchar;
typedef unsigned int uint;

//unsigned char PWM_COUNT; //计数
//unsigned int HUXI_COUNT;    //占空比更新时间
//unsigned char PWM_VLAUE;    //占空比比对值
//bit direc_flag;             //占空比更新方向

#define LED    P2
uchar dat = 0xfe;
void timer0_init() {
    TMOD=0x02;          //模式设置，00010000，定时器0，工作于模式2（M1=1，M0=0）
    TH0=256-100;               //定时器溢出值设置，每隔200us发起一次中断。
    TL0=256-100;
    TR0=1;                  //定时器0开始计时
    ET0=1;                  //开定时器0中断
    EA=1;                       //开总中断
//    PWM_COUNT =0;
}

void main() {
//    HUXI_COUNT = 0;
//    PWM_COUNT = 0;
//    PWM_VLAUE = 0;
//    direc_flag = 0;

    LED = 1;            //默认LED熄灭
    timer0_init();      //定时器0初始化
    while(1) {
        if(dat==0xff) dat=0xfe;
    }
}
void time0() interrupt 1 {
    static uchar PWM_COUNT=0; //计数
    static uint HUXI_COUNT=0;    //占空比更新时间
    static uchar PWM_VLAUE=0;    //占空比比对值
    static bit flag=0;
    PWM_COUNT++;//中断次数，每中断一次+1,　　10 归零
    HUXI_COUNT++;
    ///　          PWM_VLAUE ~ 10　为 占空比
    if(PWM_COUNT == PWM_VLAUE)      //判断是否到了点亮LED的时候
			if(dat==0xff) dat=0xfe;
        LED = dat;                    //点亮LED
    if(PWM_COUNT == 10) {           //当前周期结束
        LED = ~dat;                    //熄灭LED
        PWM_COUNT = 0;              //重新计时
    }
    if((HUXI_COUNT >= 700) && (flag == 0)) {
        //占空比增加10%
        HUXI_COUNT = 0;
        PWM_VLAUE++;
        dat = dat<<1 | 0x01;
        if(PWM_VLAUE >= 9)          //占空比更改方向
            flag = 1;
    }
    if((HUXI_COUNT >= 700) && (flag == 1)) {
        //占空比减少10%
        HUXI_COUNT = 0;
        PWM_VLAUE--;
				dat = dat<<1 | 0x01;
        if(PWM_VLAUE <= 1)          //占空比更改方向

            flag = 0;
    }
}


#else
#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define LED P2 /*硬件为 P1 口输出，大家相应改一下 */
uchar i=0;
uchar Position=0x01; /**/
void Delay(uchar n)
{
    uchar i,j,k;
    for(i=n; i>0; i--)
        for(j=100; j>0; j--)
            for(k=100; k>0; k--);
}
void T0_INT(void)interrupt 1
{
    uchar dis_tmp;
    dis_tmp=Position;
    TH0=65432/256;/* 定时器 T0 的中断时间就是固定脉宽，大家仔细看一下就会明白了 */
    TL0=65432%256;
    if(i<100)i++;
    else i=0;
    LED=~dis_tmp;/* 我的硬件设计是低电平点亮 LED ，就是灌电流 ~*/
    if(i%10==0) /*调整周期，旁边第一盏灯的周期为脉宽的 10 倍*/
    {
        dis_tmp|=dis_tmp<<1|dis_tmp>>1;
        LED=~dis_tmp;
    }
    if(i==0)/* 旁边第二盏灯的周期为脉宽的 100 倍 */
    {
        dis_tmp|=dis_tmp<<1|dis_tmp>>1|dis_tmp<<2|dis_tmp>>2;
        LED=~dis_tmp;
    }
}
void main(void)
{
    uchar k,g;
    ET0=1;
    TMOD=0X01;
    EA=1;
    TH0=55532/256;
    TL0=55532%256;
    TR0=1;
    while(1)
    {
        for(g=2; g>0; g--)
        {
            for(k=7; k>0; k--)
            {
                Position<<=1;
                Delay(g);
            }
            for(k=7; k>0; k--)
            {
                Position>>=1;
                Delay(g);
            }
        }
        for(g=0; g<2; g++)
        {
            for(k=7; k>0; k--)
            {
                Position<<=1;
                Delay(g);
            }
            for(k=7; k>0; k--)
            {
                Position>>=1;
                Delay(g);
            }
        }
    }
}

   
#endif








