#include<reg52.h>
#include"key.h"

/**
	��ʱ����ֵ����
*/
#define     count                    50000
#define     THx                      (65536 - count) / 256
#define     TLx                      (65536 - count) % 256

/**
	���ܺ궨��
*/
#define     GREEN_FLASHING_COUNT     3 // �̵Ƶ���ʱ��˸���� , �ĳ� 0 ��Ϊ����˸

#define     YELLOW_TIME              2  //�Ƶ�����ʱ��
#define     TIME_SMALL               20 //�ɵ�ʱ������
#define     TIME_BIG                 60 //�ɵ�ʱ������
#define     TIME 		             10 //��ʼʱ��

/**
	����ܶ������
*/
#define   NS_Display     P0
#define   EW_Display     P1

/**
	LED��λ����
*/
sbit NS_LED_Red    = P3^0; // �ϱ�
sbit NS_LED_Yellow = P3^1;
sbit NS_LED_Green  = P3^2;

sbit EW_LED_Red    = P3^3; // ����
sbit EW_LED_Yellow = P3^4;
sbit EW_LED_Green  = P3^5;

/**
	�����λ����
*/
sbit bit_0 = P2^0;
sbit bit_1 = P2^1;

uchar code duanxuan[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

uchar sec  = TIME; // ����
uchar secCache = TIME; // �ڵ���ʱ��ĺ�Ҫ�ѵ�����ʱ�䱣��
uchar state = 1; // LED �Ƶ�״̬

bit FLASHING = 1; // ��˸����

/**
	��ʱ����
*/
void delay(uint i)
{
    while(i--);
}

/**
	�������ʾ����
*/
void display()
{
    if(state == 1 || state == 2)	//״̬1��״̬2���������ϱ���2��
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
    else if(state == 3 || state == 4)//״̬3��״̬4���ϱ��ȶ�����2��
    {
        bit_0 = 0;
        bit_1 = 1;

        EW_Display = duanxuan[sec % 10];
        delay(100);
        EW_Display = 0x00;
        if(sec > YELLOW_TIME)
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
        if(sec > YELLOW_TIME)
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
    else if(state == 6 || state == 7 || state == 8)	 //·��ͨ�й���
    {
        bit_0 = 0;
        bit_1 = 1;

        NS_Display = 0x3f; // 0x3f �� 8��Ҳ���Ըĳ�0x00
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

        if((sec - YELLOW_TIME) > GREEN_FLASHING_COUNT)
            NS_LED_Green = 0;
        else
        {
			NS_LED_Green = FLASHING;
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

        if((sec - YELLOW_TIME) > GREEN_FLASHING_COUNT)
            EW_LED_Green = 0;
        else
        {
			NS_LED_Green = 0;
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
    else if(state == 5)	 //�ص�s1
    {
        state = 1;
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
    uchar k = Read_Key();
    static uchar i = 0;
    static uchar stateCache = 0;
    if(k == 4) {
        i++;
		if(i == 1)
		{
			stateCache = state;
		}
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
		state = stateCache;
		stateCache = 0;
        TR0 = 1;
        i = 0;
    }
}

/**
	��ʱ����ʼ������
*/
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
void main(void)
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
	j++;
    if(j == 20)
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











