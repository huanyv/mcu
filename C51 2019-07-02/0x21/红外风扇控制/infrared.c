#include "infrared.h"
#include "timer.h"


extern uint speed;


uchar IrValue[6];
uchar Time;

bit FLAG = 0; // �ֶ��Զ��л���־λ
bit FLAG1 = 0; // ��ͣ��־λ

void Intrared_SPEED_Ctrl(void)
{
	
	if(IrValue[2] == 0x07)
	{
		speed = 2;
		IrValue[2] = 0;
	}
	else if(IrValue[2] == 0x16)
	{
		speed = 5;
		IrValue[2] = 0;
	}
	else if(IrValue[2] == 0x0C)
	{
		speed = 10;
		IrValue[2] = 0;
	}
	

	

}

void Intrared_MODE_Ctrl(void)
{
	if(IrValue[2] == 0x47)  // ��
	{
		FLAG1 = 1;
		TR0 = 1;
		ET0 = 1;
		IrValue[2] = 0;
	}
	if(IrValue[2] == 0x40) // ͣ
	{
		FLAG1 = 0;
		TR0 = 0;
		ET0 = 0;
		motor = 1;		
		IrValue[2] = 0;
	}
	
	if(IrValue[2] == 0x19) // �ֶ� 
	{
		FLAG = 0;
		IrValue[2] = 0;
	}
	if(IrValue[2] == 0x18) // �Զ�
	{
		FLAG = 1;		
		IrValue[2] = 0;
	}
	
}

void IrInit(void)
{
	IT0=1;//�½��ش���
	EX0=1;//���ж�0����
	EA=1;	//�����ж�

	IRIN=1;//��ʼ���˿�
}

void ReadIr() interrupt 0
{
	uchar j,k;
	uint err;
	Time=0;					 
	delay(700);	//7ms
	if(IRIN==0)		//ȷ���Ƿ���Ľ��յ���ȷ���ź�
	{	 
		
		err=1000;				//1000*10us=10ms,����˵�����յ�������ź�
		/*������������Ϊ����ѭ���������һ������Ϊ�ٵ�ʱ������ѭ������ó�������ʱ
		�������������*/	
		while((IRIN==0)&&(err>0))	//�ȴ�ǰ��9ms�ĵ͵�ƽ��ȥ  		
		{			
			delay(1);
			err--;
		} 
		if(IRIN==1)			//�����ȷ�ȵ�9ms�͵�ƽ
		{
			err=500;
			while((IRIN==1)&&(err>0))		 //�ȴ�4.5ms����ʼ�ߵ�ƽ��ȥ
			{
				delay(1);
				err--;
			}
			for(k=0;k<4;k++)		//����4������
	 		{				
				for(j=0;j<8;j++)	//����һ������
				{

					err=60;		
					while((IRIN==0)&&(err>0))//�ȴ��ź�ǰ���560us�͵�ƽ��ȥ
					{
						delay(1);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0))	 //����ߵ�ƽ��ʱ�䳤�ȡ�
					{
						delay(10);	 //0.1ms
						Time++;
						err--;
						if(Time>30)
						{
							return;
						}
					}
					IrValue[k]>>=1;	 //k��ʾ�ڼ�������
					if(Time>=8)			//����ߵ�ƽ���ִ���565us����ô��1
					{
						IrValue[k]|=0x80;
					}
					Time=0;		//����ʱ��Ҫ���¸�ֵ							
				}
			}
		}
		if(IrValue[2]!=~IrValue[3])
		{
			return;
		}
	}			
}
