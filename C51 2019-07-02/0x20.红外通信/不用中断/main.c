#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

sbit OUT=P3^2;

uchar temp[6],time;

uchar code smgduan[17]= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                         0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0X76
                        };
void delay(uint iii)
{
    while(iii--);
}

void display()
{
    uchar i;
    for(i=0; i<3; i++)
    {
        switch(i)
        {
        case 0:
            LSC=0;
            LSB=0;
            LSA=0;
            P0=smgduan[16];
            break;
        case 1:
            LSC=0;
            LSB=0;
            LSA=1;
            P0=smgduan[temp[2]%16];
            break;
        case 2:
            LSC=0;
            LSB=1;
            LSA=0;
            P0=smgduan[temp[2]/16];
            break;
        }
        delay(100);
        P0=0x00;
    }
}


void infrared()
{
    uchar i,j;
    uint t;
    time=0;
    delay(700);
    if(OUT==0)
    {
        t=1000;
        while((OUT==0)&&(t>0))
        {
            delay(1);
            t--;
        }
        if(OUT==1)
        {
            t=500;
            while((OUT==1)&&(t>0))
            {
                delay(1);
                t--;
            }
            for(i=0; i<4; i++)
                for(j=0; j<8; j++)
                {
                    t=60;
                    while((OUT==0)&&(t>0))
                    {
                        delay(1);
                        t--;
                    }
                    t=500;
                    while((t>0)&&(OUT==1))
                    {
                        delay(10);
                        time++;
                        t--;
                        if(time>30)
                        {
                            return;
                        }
                    }
                    temp[i]=temp[i]>>1;
                    if(time>8)
                    {
                        temp[i]=temp[i]|0x80;
                    }
                    time=0;
                }
        }
        if(temp[2]!=~temp[3])
        {
            return;
        }
    }
}

int main()
{
    OUT=1;
    while(1)
    {
        display();
        infrared();
    }
    return 0;
}