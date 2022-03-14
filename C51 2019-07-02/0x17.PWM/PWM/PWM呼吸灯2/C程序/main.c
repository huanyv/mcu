#include <REG52.H>

typedef unsigned char uchar;
typedef unsigned int uint;

//unsigned char PWM_COUNT; //����
//unsigned int HUXI_COUNT;    //ռ�ձȸ���ʱ��
//unsigned char PWM_VLAUE;    //ռ�ձȱȶ�ֵ
//bit direc_flag;             //ռ�ձȸ��·���

#define LED    P2

void timer0_init()
{
    TMOD=0x02;          //ģʽ���ã�00010000����ʱ��0��������ģʽ2��M1=1��M0=0��
    TH0=256-100;               //��ʱ�����ֵ���ã�ÿ��200us����һ���жϡ�
    TL0=256-100;
    TR0=1;                  //��ʱ��0��ʼ��ʱ
    ET0=1;                  //����ʱ��0�ж�
    EA=1;                       //�����ж�
//    PWM_COUNT =0;
}

void main()
{
//    HUXI_COUNT = 0;
//    PWM_COUNT = 0;
//    PWM_VLAUE = 0;
//    direc_flag = 0;
    LED = 1;            //Ĭ��LEDϨ��   
    timer0_init();      //��ʱ��0��ʼ��
    while(1);
}
void time0() interrupt 1
{  
	static uchar PWM_COUNT=0; //����
	static uint HUXI_COUNT=0;    //ռ�ձȸ���ʱ��
	static uchar PWM_VLAUE=0;    //ռ�ձȱȶ�ֵ
	static bit flag=0;  
    PWM_COUNT++;//�жϴ�����ÿ�ж�һ��+1,����10 ����
    HUXI_COUNT++;
		if(PWM_COUNT == 10)PWM_COUNT = 0;
	
    if(PWM_COUNT < PWM_VLAUE)      //�ж��Ƿ��˵���LED��ʱ��
        LED = 0XFF;                   
    else         //��ǰ���ڽ���
        LED = 0X00;    
			
    if((HUXI_COUNT >= 700) && (flag == 0))
    {                               //ռ�ձ�����10%
        HUXI_COUNT = 0;
        PWM_VLAUE++;
        if(PWM_VLAUE >= 9)          //ռ�ձȸ��ķ���
            flag = 1; 
    }
    if((HUXI_COUNT >= 700) && (flag == 1))
    {                               //ռ�ձȼ���10%
        HUXI_COUNT = 0;
        PWM_VLAUE--;
        if(PWM_VLAUE <= 1)          //ռ�ձȸ��ķ���
            flag = 0; 
    }   
}











