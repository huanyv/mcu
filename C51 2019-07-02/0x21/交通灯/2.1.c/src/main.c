#include<reg52.h>
#include"key.h"

#define   count          50000
#define   THx            (65536-count)/256
#define   TLx            (65536-count)%256

#define   YELLOW_TIME    5  //黄灯亮的时间
#define   TIME_SMALL     20 //最大时间
#define   TIME_BIG       60 //最小时间
#define   TIME 		     10 //初始时间

#define   NS_Display     P0
#define   EW_Display     P1

sbit NS_LED_Red    = P3^0;
sbit NS_LED_Yellow = P3^1;
sbit NS_LED_Green  = P3^2;

sbit EW_LED_Red    = P3^3;
sbit EW_LED_Yellow = P3^4;
sbit EW_LED_Green  = P3^5;

sbit bit_0 = P2^0;
sbit bit_1 = P2^1;

uchar code duanxuan[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

uchar sec  = TIME;
uchar secCache = TIME;
uchar state = 1;

bit FLASHING = 0;

void delay(uint i)
{
    while(i--);
}

void display()
{
    if(state == 1 || state == 2)	//状态1和状态2，东西比南北少2秒
    {
        bit_0 = 0;
        bit_1 = 1;

        NS_Display = duanxuan[ sec % 10 ];
        delay(100);
        NS_Display = 0x00;
        if(sec > YELLOW_TIME)
        {
            EW_Display = duanxuan[ (sec - YELLOW_TIME) % 10 ];
            delay(200);
            EW_Display = 0x00;
        }
        else
        {
            EW_Display = duanxuan[sec % 10];
            delay(200);
            EW_Display = 0x00;
        }

        bit_0 = 1;
        bit_1 = 0;

        NS_Display = duanxuan[sec / 10];
        delay(100);
        NS_Display = 0x00;
        if(sec > YELLOW_TIME)
        {
            EW_Display = duanxuan[ (sec - YELLOW_TIME) / 10 ];
            delay(200);
            EW_Display = 0x00;
        }
        else
        {
            EW_Display = duanxuan[sec / 10];
            delay(200);
            EW_Display = 0x00;
        }
    }
    else if(state == 3 || state == 4)//状态3和状态4，南北比东西少2秒
    {
        bit_0 = 0;
        bit_1 = 1;

        EW_Display = duanxuan[sec % 10];
        delay(100);
        EW_Display = 0x00;
        if(sec>YELLOW_TIME)
        {
            NS_Display = duanxuan[ (sec - YELLOW_TIME) % 10 ];
            delay(200);
            NS_Display = 0x00;
        }
        else
        {
            NS_Display = duanxuan[sec % 10];
            delay(200);
            NS_Display = 0x00;
        }

        bit_0 = 1;
        bit_1 = 0;

        EW_Display = duanxuan[sec / 10];
        delay(100);
        EW_Display = 0x00;
        if(sec>YELLOW_TIME)
        {
            NS_Display = duanxuan[ (sec - YELLOW_TIME) / 10 ];
            delay(200);
            NS_Display = 0x00;
        }
        else
        {
            NS_Display = duanxuan[sec / 10];
            delay(200);
            NS_Display = 0x00;
        }
    }
    else if(state == 6 || state == 7 || state == 8)	 //路口通行管理
    {
        bit_0 = 0;
        bit_1 = 1;

        NS_Display = 0x3f;
        delay(100);
        NS_Display = 0x00;
        EW_Display = 0x3f;
        delay(100);
        EW_Display = 0x00;

        bit_0 = 1;
        bit_1 = 0;

        NS_Display = 0x3f;
        delay(100);
        NS_Display = 0x00;
        EW_Display = 0x3f;
        delay(100);
        EW_Display = 0x00;
    }
}

void led_display()
{
    if(state == 1)	//s1
    {
        EW_LED_Red = 0;
        EW_LED_Green = 1;
        EW_LED_Yellow = 1;

        NS_LED_Red = 1;

        if((sec - 5) > 3)
            NS_LED_Green = 0;
        else
        {
            if(FLASHING == 1)
                NS_LED_Green  = 0;
            if(FLASHING == 0)
                NS_LED_Green = 1;
        }

        NS_LED_Yellow = 1;
    }
    else if(state == 2) //s2
    {
        EW_LED_Red = 0;
        EW_LED_Green = 1;
        EW_LED_Yellow = 1;

        NS_LED_Red = 1;
        NS_LED_Green = 1;
        NS_LED_Yellow = 0;

    }
    else if(state==3) //s3
    {
        EW_LED_Red=1;

        if((sec - 5) > 3)
            EW_LED_Green = 0;
        else
        {
            if(FLASHING == 1)
                EW_LED_Green = 0;
            if(FLASHING == 0)
                EW_LED_Green = 1;
        }

        EW_LED_Yellow = 1;

        NS_LED_Red = 0;
        NS_LED_Green = 1;
        NS_LED_Yellow = 1;
    }
    else if(state == 4)	//s4
    {
        EW_LED_Red = 1;
        EW_LED_Green = 1;
        EW_LED_Yellow = 0;


        NS_LED_Red = 0;
        NS_LED_Green = 1;
        NS_LED_Yellow = 1;
    }
    else if(state == 5)	 //回到s1
    {
        state = 1;//一共四个状态
    }
    else if(state == 6)
    {
        EW_LED_Red = 1;
        EW_LED_Green = 1;
        EW_LED_Yellow = 0;

        NS_LED_Red = 1;
        NS_LED_Green = 1;
        NS_LED_Yellow = 0;
    }
    else if(state == 7)
    {
        EW_LED_Red = 1;
        EW_LED_Green = 0;
        EW_LED_Yellow = 1;

        NS_LED_Red = 0;
        NS_LED_Green = 1;
        NS_LED_Yellow = 1;
    }
    else
    {
        EW_LED_Red = 0;
        EW_LED_Green = 1;
        EW_LED_Yellow = 1;

        NS_LED_Red = 1;
        NS_LED_Green = 0;
        NS_LED_Yellow = 1;
    }
}
void key()
{
    uchar k = 0;
    static uchar i = 0;
    k = Read_Key();
    if(k == 4) {
        i++;
        TR0 = 0;
    }
    if(k == 3 && TR0 == 0 && sec < TIME_BIG && (state == 1 || state == 2 || state == 3 || state == 4))
    {
        sec = sec + YELLOW_TIME;
        secCache = sec;
    }
    if(k == 2 && TR0 == 0 && sec > TIME_SMALL && (state == 1 || state == 2 || state == 3 || state == 4))
    {
        sec = sec - YELLOW_TIME;
        secCache = sec;
    }
    if(k == 1 && (state == 1 || state == 2 || state == 3 || state == 4))
    {
        TR0 = ~TR0;
    }
    if(i == 1) {
        state = 6;
    }
    if(i == 2) {
        state = 7;
    }
    if(i == 3) {
        state = 8;
    }
    if(i == 4) {
        state = 1;
        TR0 = 1;
        i = 0;
    }
}

void Tim_Init()
{
    TMOD = 0x11;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
    ET1 = 1;
    TR1 = 1;
    TH0 = THx;
    TL0 = TLx;
    TH1 = THx;
    TL1 = TLx;
}
void main()
{
    Tim_Init();
    while(1)
    {
        display();
        led_display();
        key();
    }
}

void TIME0() interrupt 1
{
    static uchar j = 0;
    TH0 = THx;
    TL0 = TLx;
    if(++j == 20)
    {
        j = 0;
        sec--;
        if(sec == 0)
        {
            sec = secCache;
            state++;//s3

        }
        if(sec - YELLOW_TIME == 0)
        {
            state++;//s2	   s4
        }
    }
}

void TIME1() interrupt 3
{
    static uchar j = 0;
    TH1 = THx;
    TL1 = TLx;
    if(++j == 10) {
        j = 0;
        FLASHING = ~FLASHING;
    }
}
















