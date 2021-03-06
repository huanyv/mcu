#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

#define dula P0

#define count 50000
#define THx (65536-count)/256
#define TLx (65536-count)%256

sbit A38=P2^2;
sbit B38=P2^3;
sbit C38=P2^4;

sbit buzzer=P1^5;

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;

bit flag_s=0,flag_m=0,flag_h=0;

uchar code distab[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                         0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x40
                        };
uchar min=0,hour=0,sec=0;

uchar flag=0;

void delay(uint iii)
{
    while(iii--);
}
void display()
{
    uchar i;
    for(i=1; i<9; i++)
    {
        switch(i)
        {
        case 1:
            C38=0;
            B38=0;
            A38=0;
            if(flag_s==0)
            {
                dula=distab[sec%10];
            }
            else
            {
                dula=0x00;
            }
            break;
        case 2:
            C38=0;
            B38=0;
            A38=1;
            if(flag_s==0)
            {
                dula=distab[sec/10];
            }
            else
            {
                dula=0x00;
            }
            break;

        case 3:
            C38=0;
            B38=1;
            A38=0;
            dula=0x40;
            break;


        case 4:
            C38=0;
            B38=1;
            A38=1;
            if(flag_m==0)
                dula=distab[min%10];
            else
            {
                dula=0x00;
            }
            break;
        case 5:
            C38=1;
            B38=0;
            A38=0;
            if(flag_m==0)
                dula=distab[min/10];
            else
            {
                dula=0x00;
            }
            break;

        case 6:
            C38=1;
            B38=0;
            A38=1;
            dula=0x40;
            break;


        case 7:
            C38=1;
            B38=1;
            A38=0;
            if(flag_h==0)
                dula=distab[hour%10];
            else
            {
                dula=0x00;
            }
            break;
        case 8:
            C38=1;
            B38=1;
            A38=1;
            if(flag_h==0)
                dula=distab[hour/10];
            else
            {
                dula=0x00;
            }
            break;

        }
        delay(130);
        dula=0x00;

    }
}
void timer_init()
{
    TMOD=0x11;
    ET0=1;
    EA=1;;
    ET1=1;
    TH0=THx;
    TL0=TLx;
    TH1=THx;
    TL1=TLx;
}
void key_ctrl()//????????
{
    static bit flag_song=0;//????????????
    static uint flag_time=0;
    if(flag_song==0&&k1==0)
    {
        flag_time++;
        if(flag_time>3&&k1==0)
        {
            flag_time=0;
            flag_song=1;
            if((sec!=0||min!=0||hour!=0)&&flag==0)
            {
                TR0=~TR0;
            }
        }
    }
    if(flag_song==0&&k2==0)//k2??????????????-
    {
        flag_time++;
        if(flag_time>3&&k2==0)
        {
            flag_time=0;
            flag_song=1;
            if((sec!=0||min!=0||hour!=0)&&flag==0&&TR0==0)
            {
                sec=0;
                min=0;
                hour=0;
            }
            else if(flag==1)
            {
                sec--;
                if(sec==255)sec=59;
            }
            else if(flag==2)
            {
                min--;
                if(min==255)min=59;
            }
            else if(flag==3)
            {
                hour--;
                if(hour==255)hour=99;
            }
        }

    }
    if(flag_song==0&&k3==0)//k3????????+
    {
        flag_time++;
        if(flag_time>3&&k3==0)
        {
            flag_time=0;
            flag_song=1;
            if(flag==1&&TR0==0)
            {
                sec++;
                if(sec==60)sec=0;
            }
            if(flag==2&&TR0==0)
            {
                min++;
                if(min==60)min=0;
            }
            if(flag==3&&TR0==0)
            {
                hour++;
                if(hour==100)hour=0;
            }
        }
    }

    if(flag_song==0&&k4==0)//????????
    {
        flag_time++;
        if(flag_time>3&&k4==0)
        {
            flag_time=0;
            flag_song=1;
            flag++;
        }
    }


    if(flag==1&&TR0==0)//????????
    {
        TR1=1;
        flag_m=0;
        flag_h=0;
    }
    else if(flag==2&&TR0==0)//????????
    {
        TR1=1;
        flag_s=0;
        flag_h=0;
    }
    else if(flag==3&&TR0==0)//????????
    {
        TR1=1;
        flag_s=0;
        flag_m=0;
    }
    else if(flag==4&&TR0==0)//????????
    {
        TR1=0;
        flag=0;
        flag_m=0;
        flag_s=0;
        flag_h=0;
    }
    if(k1==1&&k2==1&&k3==1&&k4==1)//????
    {
        flag_time=0;
        flag_song=0;
    }

    if(hour==0&&min==0&&sec==0)// ??????????????
    {
        TR0=0;
//		while(sec<9999)
//		{
//			if(k1==0)
//			{
//				delay(1500);
//				if(k1==0)
//				{
//					break;
//				}
//			}
//		}
    }
}
void main()
{
    timer_init();
    while(1)
    {
        display();
        key_ctrl();
    }
}
void timer0() interrupt 1
{
    static i=0;
    TH0=THx;
    TL0=TLx;
    if(++i==20)
    {
        i=0;
        sec--;
        if(sec==255)
        {
            sec=59;
            min--;

            if(min==255)
            {
                min=59;
                hour--;
                if(hour==0&&min==0&&sec==0)
                {
                    TR0=0;
                }
            }
        }
    }
}
void timer1() interrupt 3
{
    static i=0;
    TH1=THx;
    TL1=TLx;
    if(++i==13)
    {
        i=0;
        if(flag==1)
        {
            flag_s=~flag_s;
        }
        if(flag==2)
        {
            flag_m=~flag_m;
        }
        if(flag==3)
        {
            flag_h=~flag_h;
        }

    }
}