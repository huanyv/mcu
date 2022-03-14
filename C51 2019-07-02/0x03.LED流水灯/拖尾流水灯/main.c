#if 0

#include <REG52.H>

typedef unsigned char uchar;
typedef unsigned int uint;

//unsigned char PWM_COUNT; //����
//unsigned int HUXI_COUNT;    //ռ�ձȸ���ʱ��
//unsigned char PWM_VLAUE;    //ռ�ձȱȶ�ֵ
//bit direc_flag;             //ռ�ձȸ��·���

#define LED    P2
uchar dat = 0xfe;
void timer0_init() {
    TMOD=0x02;          //ģʽ���ã�00010000����ʱ��0��������ģʽ2��M1=1��M0=0��
    TH0=256-100;               //��ʱ�����ֵ���ã�ÿ��200us����һ���жϡ�
    TL0=256-100;
    TR0=1;                  //��ʱ��0��ʼ��ʱ
    ET0=1;                  //����ʱ��0�ж�
    EA=1;                       //�����ж�
//    PWM_COUNT =0;
}

void main() {
//    HUXI_COUNT = 0;
//    PWM_COUNT = 0;
//    PWM_VLAUE = 0;
//    direc_flag = 0;

    LED = 1;            //Ĭ��LEDϨ��
    timer0_init();      //��ʱ��0��ʼ��
    while(1) {
        if(dat==0xff) dat=0xfe;
    }
}
void time0() interrupt 1 {
    static uchar PWM_COUNT=0; //����
    static uint HUXI_COUNT=0;    //ռ�ձȸ���ʱ��
    static uchar PWM_VLAUE=0;    //ռ�ձȱȶ�ֵ
    static bit flag=0;
    PWM_COUNT++;//�жϴ�����ÿ�ж�һ��+1,����10 ����
    HUXI_COUNT++;
    ///��          PWM_VLAUE ~ 10��Ϊ ռ�ձ�
    if(PWM_COUNT == PWM_VLAUE)      //�ж��Ƿ��˵���LED��ʱ��
			if(dat==0xff) dat=0xfe;
        LED = dat;                    //����LED
    if(PWM_COUNT == 10) {           //��ǰ���ڽ���
        LED = ~dat;                    //Ϩ��LED
        PWM_COUNT = 0;              //���¼�ʱ
    }
    if((HUXI_COUNT >= 700) && (flag == 0)) {
        //ռ�ձ�����10%
        HUXI_COUNT = 0;
        PWM_VLAUE++;
        dat = dat<<1 | 0x01;
        if(PWM_VLAUE >= 9)          //ռ�ձȸ��ķ���
            flag = 1;
    }
    if((HUXI_COUNT >= 700) && (flag == 1)) {
        //ռ�ձȼ���10%
        HUXI_COUNT = 0;
        PWM_VLAUE--;
				dat = dat<<1 | 0x01;
        if(PWM_VLAUE <= 1)          //ռ�ձȸ��ķ���

            flag = 0;
    }
}


#else
#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define LED P2 /*Ӳ��Ϊ P1 ������������Ӧ��һ�� */
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
    TH0=65432/256;/* ��ʱ�� T0 ���ж�ʱ����ǹ̶����������ϸ��һ�¾ͻ������� */
    TL0=65432%256;
    if(i<100)i++;
    else i=0;
    LED=~dis_tmp;/* �ҵ�Ӳ������ǵ͵�ƽ���� LED �����ǹ���� ~*/
    if(i%10==0) /*�������ڣ��Աߵ�һյ�Ƶ�����Ϊ����� 10 ��*/
    {
        dis_tmp|=dis_tmp<<1|dis_tmp>>1;
        LED=~dis_tmp;
    }
    if(i==0)/* �Աߵڶ�յ�Ƶ�����Ϊ����� 100 �� */
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








