#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char
#define uint  unsigned int
sbit OutPut=P1^7;                       //矩形波输出口
sbit input=P1^0;
float fosc=12000000;                     //系统时钟频率
float length=65536;                      //方式1计数长度
uchar flag,i=8,kz;		                         //状态键标志
uchar ZKB;		                         //占空比
uint  PL,TT=50,TTT=50;		                        //频率
uchar TIMER0_L,TIMER0_H,TIMER1_L,TIMER1_H;
//T0和T1的定时初值
uchar code tabl[11]=
{0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0};      //LED共阴极代码
/*****************************************
                      系统初始化
*****************************************/
void system_init(void )
{
    SCON=0x00;
    flag=0;
    PL=20;
    ZKB=50;
    TL0=0xb0;				   //初始频率20Hz定时0.05s
    TH0=0x3c;
    TL1=0x58;				   //初始占空比50定时0.025s
    TH1=0x9e;
    TMOD=0x11;          //T0和T1为工作方式1的定时模式
    IT0=1;                    //选择INT0为下降沿触发方式
    IT1=1;                   //选择INT1为下降沿触发方式
    EX0=1;
    EX1=1;                   //外部中断0允许
    ET0=1;                   //定时器1和定时器0中断允许
    ET1=1;
    EA=1;                    //系统中断允许
    TR0=1;                   //定时器1和定时器0开始定时
    TR1=1;
    TIMER0_L=0xb0;
    TIMER0_H=0x3c;
    TIMER1_L=0x58;
    TIMER1_H=0x9e;
}
/*****************************************

*****************************************/

void display(uint m,uchar n)
{
    PL=PL%1000;
    d=PL/100;
    PL=PL%100;
    e=PL/10;
    k=PL%10;

    m=ZKB/10;			               //分离占空比各位数值
    n=ZKB%10;
    if(PL==0)
        b=f=d=e=k=10;
    if(ZKB==0)
        m=n=10;
    P2=~0x01;
    P0=tabl[b];
    delay1ms(2);
    P2=~0x02;
    P0=tabl[f];
    delay1ms(2);
    P2=~0x04;
    P0=tabl[d];
    delay1ms(2);
    P2=~0x08;
    P0=tabl[e];
    delay1ms(2);
    P2=~0x10;
    P0=tabl[k];
    delay1ms(2);
    P2=~0x40;
    P0=tabl[m];
    delay1ms(2);
    P2=~0x80;
    P0=tabl[n];
    delay1ms(2);
}


/*****************************************
            键盘扫描
*****************************************/
void Key_Scan()
{   float TC0,TC1;
    flag++;
    if(flag==3)						       //状态返回，正常工作
    {
        flag=0;			                	 //清状态标志位
        TC0=(length-(fosc*(100-ZKB))/(12*100*PL));
        TC1=(length-(fosc*ZKB)/(12*100*PL));    //占空比定时初值
        TIMER0_H=(uint)TC0/256;           //计算T0和T1的初值
        TIMER0_L=(uint)TC0%256;
        TIMER1_H=(uint)TC1/256;
        TIMER1_L=(uint)TC1%256;
    }
}
void Key_Scan1()
{
    if(flag==1)
    {
        PL+=10;                        //按键频率加5
        if(PL>10000) PL=50;
        display(PL,ZKB);
    }
    if(flag==2)			       //状态2下对占空比进行调整
    {
        ZKB+=5;                  //按键占空比加5
        if(ZKB>99) ZKB=5;
    }
    if(flag==3)			       //状态2下对占空比进行调整
    {
        flag=0;
        display(PL,ZKB);
    }
    display(PL,ZKB);
}
void  ccdd()	   interrupt 0
{
    EX0=0;
    kz=kz<<1;
    i--;
    if(input)
        kz=kz|0x01;
    if(~input)
        kz=kz&0xfe;
    if(~i)
    {
        if(kz==0xaa)
            Key_Scan();
        if(kz==0xbb)
            Key_Scan1();
        i=8;
    }
    EX0=1;
}
/*****************************************
             主函数
*****************************************/
void main()
{
    uint PL0=0;
    uchar ZKB0=0;
    system_init();            	//系统初始化
    while(1)							//死循环，显示频率和占空比
    {
        if(flag==0)               //状态0时，正常显示频率和占空比
            display(PL,ZKB);
        if(flag==1)            //状态1时，频率调整状态，频率闪烁
        {
            display(PL0,ZKB);
            TT--;
            if(TT==0)
            {   TT=50;
                while(TT--)
                {
                    display(PL,ZKB);
                }
                TT=50;
            }
        }
        if(flag==2)       //状态2时，占空比调整状态，占空比闪烁
        {
            display(PL,ZKB0);
            TTT--;
            if(TTT==0)
            {   TTT=50;
                while(TTT--)
                {
                    display(PL,ZKB);
                }
                TTT=50;
            }
        }
    }
}
