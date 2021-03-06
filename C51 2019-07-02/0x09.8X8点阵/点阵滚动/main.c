#include<reg51.h>
#include<intrins.h>

//--定义要使用的IO口--//
#define COMMONPORTS                P0
sbit SRCLK= P3 ^ 6;
sbit RCLK = P3 ^ 5;
sbit SER  = P3 ^ 4;
sbit KEY1 = P3 ^ 0; //按键2用于时间设置
sbit KEY2 = P3 ^ 2; //按键3用于时间设置加
sbit KEY3 = P3 ^ 3;        //按键4用于时间设置减

unsigned char Time,time_hrs=20,time_min=59,time_sec=35;
unsigned char MENU;//菜单切换标志位
//--列选通控制--//
unsigned char code TAB[8]  = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};

//--点阵字码--//
unsigned char code CHARCODE [113]=
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //空白
    0x3e,0x41,0x41,0x41,0x3e,0x00,          //0
    0x11,0x21,0x7F,0x01,0x01,0x00,          //1
    0x21,0x43,0x45,0x49,0x31,0x00,          //2
    0x22,0x41,0x49,0x49,0x36,0x00,          //3
    0x0C,0x14,0x24,0x7F,0x04,0x00,          //4
    0x72,0x51,0x51,0x51,0x4E,0x00,          //5
    0x3E,0x49,0x49,0x49,0x26,0x00,          //6
    0x40,0x47,0x48,0x50,0x60,0x00,          //7
    0x36,0x49,0x49,0x49,0x36,0x00,          //8
    0x32,0x49,0x49,0x49,0x3E,0x00,          //9
    0x36,0x36,0x00,                                  //:
    0x3E,0x2A,0x3E,0x00,0x14,0x11,0x7F,0x10,0x00,                   //时
    0xBF,0x40,0xBE,0xAA,0xBE,0x81,0xFF,0x00,             //间
    0xA0,0x60,0x3F,0x02,0x58,0xD5,0x92,0xD6,0x59,0x00,         //设
    0xD1,0xDF,0xD5,0xF5,0xD5,0xDF,0xD1,                                   //置
    0x11,0x22,0x54,0x18,0x91,0x5F,0x20,0x10,             //分
};

unsigned char WS[50];//用来存放要显示的位数的值

/*******************************************************************************
* 函数名         : buffer_normal();
* 函数功能                 : 正常显示缓冲数组
* 输入           : 无
* 输出                  : 无
*******************************************************************************/
void buffer_normal()                                        //正常显示数组
{
    unsigned char a,b,c,d,e,f,g;
    for(g=35; g<43; g++)                                                      //空白
    {
        WS[g]=CHARCODE[g-35];
    }

    for(f=29; f<35; f++)                                                      //分钟个位
    {
        WS[f]=CHARCODE[time_min%10*6+f-21];
    }

    for(e=23; e<29; e++)
    {   //分钟十位
        WS[e]=CHARCODE[time_min%100/10*6+e-15];
    }

    for(d=20; d<23; d++)                                                      //秒点
    {
        WS[d]=CHARCODE[d+48];
    }

    for(c=14; c<20; c++)                                                      //小时个位
    {
        WS[c]=CHARCODE[time_hrs%10*6+c-6];
    }

    for(b=8; b<14; b++)                                                      //小时十位
    {
        WS[b]=CHARCODE[time_hrs%100/10*6+b];
    }

    for(a=0; a<8; a++)                                                      //空白
    {
        WS[a]=CHARCODE[a];
    }
}
/*******************************************************************************
* 函数名         : timeset();
* 函数功能                 : 时间设置显示缓冲数组
* 输入           : 无
* 输出                  : 无
*******************************************************************************/
void timeset()                                        //时间设置
{
    unsigned char a,b,c;

    for(c=42; c<50; c++)                                      //空白
    {
        WS[c]=CHARCODE[c-42];
    }

    for(b=8; b<42; b++)                                      //时间设置
    {
        WS[b]=CHARCODE[b+63];
    }

    for(a=0; a<8; a++)                              //空白
    {
        WS[a]=CHARCODE[a];
    }

}
/*******************************************************************************
* 函数名         : Hour_setting();
* 函数功能                 : 小时设置显示缓冲数组
* 输入           : 无
* 输出                  : 无
*******************************************************************************/
void Hour_setting()                                        //小时设置显示缓冲数组
{
    unsigned char a,b,c,d,e;
    for(e=28; e<36; e++)                                                      //空白
    {
        WS[e]=CHARCODE[e-28];
    }

    for(d=20; d<28; d++)                                                      //时
    {
        WS[d]=CHARCODE[d+51];
    }

    for(c=14; c<20; c++)                                                      //小时个位
    {
        WS[c]=CHARCODE[time_hrs%10*6+c-6];
    }

    for(b=8; b<14; b++)                                                      //小时十位
    {
        WS[b]=CHARCODE[time_hrs%100/10*6+b];
    }

    for(a=0; a<8; a++)                                                      //空白
    {
        WS[a]=CHARCODE[a];
    }
}
/*******************************************************************************
* 函数名         : Minute_setting();
* 函数功能                 : 分钟设置显示缓冲数组
* 输入           : 无
* 输出                  : 无
*******************************************************************************/
void Minute_setting()                                        //分钟设置显示缓冲数组
{
    unsigned char a,b,c,d,e;
    for(e=28; e<36; e++)                                                      //空白
    {
        WS[e]=CHARCODE[e-28];
    }

    for(d=20; d<28; d++)                                                      //分
    {
        WS[d]=CHARCODE[d+85];
    }

    for(c=14; c<20; c++)                                                      //分钟个位
    {
        WS[c]=CHARCODE[time_min%10*6+c-6];
    }

    for(b=8; b<14; b++)
    {   //分钟十位
        WS[b]=CHARCODE[time_min%100/10*6+b];
    }

    for(a=0; a<8; a++)                                                      //空白
    {
        WS[a]=CHARCODE[a];
    }
}

/*******************************************************************************
* 函数名         : delay();
* 函数功能                 : 延时
* 输入           : 无
* 输出                  : 无
*******************************************************************************/
void delay(unsigned int time)
{
    unsigned int i,j;
    for(i=0; i<time; i++)
        for(j=0; j<47; j++);
}
/*******************************************************************************
* 函数名         : TimerConfiguration();
* 函数功能                 : 配置定时器值
* 输入           : 无
* 输出                  : 无
*******************************************************************************/
void TimerConfiguration()
{
    TMOD = 0x01; //选择工作方式1
    TH0 = 0x3C;         //设置初始值,定时50MS
    TL0 = 0xB0;
    EA = 1;                         //打开总中断
    ET0 = 1;                 //打开定时器0中断
    TR0 = 1;                 //启动定时器0
}
/*******************************************************************************
* 函数名         : Timer0()
* 函数功能                 : 定时器0中断函数
* 输入           : 无
* 输出                  : 无
*******************************************************************************/
void Timer0() interrupt 1
{
    TH0 = 0x3C;         //设置初始值50ms
    TL0 = 0xB0;
    Time++;
    if(Time==20)
    {
        Time=0;
        time_sec++;
        if(time_sec==60)
        {
            time_sec=0;
            time_min++;
            if(time_min==60)
            {
                time_min=0;
                time_hrs++;
                if(time_hrs==24)
                {
                    time_hrs=0;
                }
            }
        }
    }
}

/*******************************************************************************
* 函数名         : Hc595SendByte(unsigned char dat);
* 函数功能                 : 向74H595发送一个字节的数据
* 输入           : 无
* 输出                  : 无
*******************************************************************************/
void Hc595SendByte(unsigned char dat)
{
    unsigned char a;
    SRCLK=0;
    RCLK=0;
    for(a=0; a<8; a++)
    {
        SER=dat>>7;
        dat<<=1;

        SRCLK=1;
        _nop_();
        _nop_();
        SRCLK=0;
    }

    RCLK=1;
    _nop_();
    _nop_();
    RCLK=0;
}
/*******************************************************************************
* 函数名         : display();
* 函数功能                 : 显示函数
* 输入           : 无
* 输出                  : 无
*******************************************************************************/
void  display(unsigned char array)
{
    unsigned char tab;
    unsigned int  a,b,c;

    for(a=0; a<8; a++)
    {
        if(a ==7)
        {
            b++;
            if(b==array)                           //数组数量减8
            {
                b=0;
            }
        }
        for(c=0; c<2; c++)                                          //控制流动速度
        {
            for(tab=0; tab<8; tab++)
            {
                Hc595SendByte(0x00);                    //消隐
                COMMONPORTS        = TAB[tab];                    //P0输出字码
                Hc595SendByte(WS[tab+b]);
                delay(1);
            }
        }
    }
}
/*******************************************************************************
* 函数名         : array_clear();
* 函数功能                 : 缓冲数组清零函数
* 输入           : 无
* 输出                  : 无
*******************************************************************************/
void  array_clear()
{
    unsigned int  a;

    for(a=0; a<50; a++)
    {
        WS[a]=0;
    }
}

/*******************************************************************************
* 函数名         : main
* 函数功能                   : 主函数
* 输入           : 无
* 输出                  : 无
*******************************************************************************/

void main()
{
    unsigned char s=0;
    MENU=0;
    TimerConfiguration();
    while(1)
    {
        if(KEY1==0)
        {
            s++;
            if(s>2)
            {
                s=0;
                MENU++;
            }
        }

        if(MENU==0)                           //正常走时
        {
            array_clear();
            buffer_normal();
            display(35);
        }

        if(MENU==1)                           //显示时间设置
        {
            timeset();
            display(42);
        }

        if(MENU==2)                           //小时设置
        {
            array_clear();
            if(KEY2==0)
            {
                s++;
                if(s>2)
                {
                    s=0;
                    time_hrs++;                 //小时加
                    if(time_hrs>23)
                    {
                        time_hrs=0;
                    }
                }
            }

            if(KEY3==0)
            {
                s++;
                if(s>2)
                {
                    s=0;
                    time_hrs--;                 //小时减
                    if(time_hrs>24)
                    {
                        time_hrs=23;
                    }
                }
            }

            Hour_setting();
            display(28);
        }

        if(MENU==3)                           //分钟设置
        {
            array_clear();
            if(KEY2==0)
            {
                s++;
                if(s>2)
                {
                    s=0;
                    time_min++;                 //分钟加
                    if(time_min>59)
                    {
                        time_min=0;
                    }
                }
            }

            if(KEY3==0)
            {
                s++;
                if(s>2)
                {
                    s=0;
                    time_min--;                 //分钟减
                    if(time_min>60)
                    {
                        time_min=59;
                    }
                }
            }

            Minute_setting();
            display(28);
        }

        if(MENU>3)
        {
            MENU=0;
            time_sec=0;
        }

    }
}