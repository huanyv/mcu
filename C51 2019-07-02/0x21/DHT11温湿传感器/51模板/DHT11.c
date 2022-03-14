#include"intrins.h"
#include"reg52.h"
#include"DHT11.h"

#	define   delay_10us()     _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_()


void delay_1ms(uint i) {
    unsigned int x;
    while(i--)
        for(x=0; x<123; x++);
}

//��ʼ��
void start()//��ʼ�ź�
{
    IO=1;
    delay_10us();
    IO=0;
    delay_1ms(20);  //�������� 18ms  ��֤�ܼ�⵽��ʼ�ź�
    IO=1;          //��⵽��ʼ�źź󣬽���ƽ����20-40us
    delay_10us();        //��ʱ20-40us
    delay_10us();
    delay_10us();
    delay_10us();
}
uchar receive_byte()//����һ���ֽ�
{
		uchar data_byte;
    uchar i,temp;
    for(i=0; i<8; i++)
    {
        while(!IO);//�ȴ�50us�ĵ͵�ƽ��ʼ�źŽ���
        delay_10us();    //��ʼ�źŽ�������ʱ26us-28us
        delay_10us();
        delay_10us();
        temp=0;   //���ʱ��Ϊ26us-28us ���ʾ���յ�����Ϊ'0'
        if(IO==1)
            temp=1;//���ʱ�䳬��26us-28us ���ʾ�յ�������Ϊ'1'
        while(IO);//�ȴ������źŸߵ�ƽ�� '0'Ϊ26us-28us��'1'Ϊ70us
        data_byte<<=1;//�����յ����������λ����
        data_byte|=temp;
    }
    return data_byte;
}

void receive(int *temp,int *hum) //��������
{
	uchar RH,RL,TH,TL;              //���ô洢��ʪ�ȵı���
	uchar R_H,R_L,T_H,T_L,check;          //����׼��У��洢��ʪ�ȵı���
	uchar i;

	start();//��ʼ�źų�ʼ��
	IO=1;   //������Ϊ����  �жϴӻ�DHT11����Ӧ�ź�             
	if(IO == RESET) //�ж��Ƿ�����Ӧ�ź�
	{
		i = 0;
		while((IO == 0)&&(i<100))//�жϴӻ�����80us�͵�ƽ�ź��Ƿ����
			i++;
		i = 0;
		while((IO == 1)&&(i<100))
			i++;

		R_H = receive_byte();//ʪ������
		R_L = receive_byte();//ʪ��С��
		T_H = receive_byte();//�¶�����
		T_L = receive_byte();//�¶�С��
		check = receive_byte();//У���
		
		IO=0;//�����е����ݽ�����ɺ󣬽��ӻ���ƽ����50us
		delay_10us();        //����50us
		delay_10us();
		delay_10us();
		delay_10us();
		delay_10us();
		IO=1;//���ӻ���ƽ���ߣ��������״̬

		if(R_H+R_L+T_H+T_L == check)//�ж϶�ȡ��������У��λ�Ƿ���ͬ
		{
			RH=R_H;
			RL=R_L;
			TH=T_H;
			TL=T_L;
		}
		*temp   = TH;
		*temp <<= 8;
		*temp  |= TL;

		*hum   =  RH;
		*hum <<=  8;
		*hum  |=  RL;
	}
}