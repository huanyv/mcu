#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

#define dula P0
#define PINC P3

//#define count 50000
//#define THx (65536-count)/256
//#define TLx (65536-count)%256

sbit A38=P2^2;
sbit B38=P2^3;
sbit C38=P2^4;

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;

uchar a=0,b=0,c=0,d=0;

uchar code distab[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d, 
						0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x40};
void delay(uint iii)
{
	while(iii--);
}
void display()
{
	uchar i;
	for(i=1;i<9;i++)
	{
		switch(i)
		{
			case 1:C38=0;B38=0;A38=0;
			dula=distab[d];break;
			case 2:C38=0;B38=0;A38=1;
			dula=distab[c];break;
			case 3:C38=0;B38=1;A38=0;
			dula=distab[b];break;
			case 4:C38=0;B38=1;A38=1;
			dula=distab[a];break;
			case 5:C38=1;B38=0;A38=0;break;
	
			
			case 6:C38=1;B38=0;A38=1;break;
						
			
			case 7:C38=1;B38=1;A38=0;break;

			case 8:C38=1;B38=1;A38=1;break;
						
		}
		delay(200);
		dula=0x00;
	}
}
uchar readkey(void)
{
	uchar keyval=0;  //////keyvai�����ռ��룬4�������ֱ��Ӧ�ļ�����0x0e,0x0d,0x0b,0x07
	uchar newkey;      ////////newkey�ǵ�ǰ���룬��Ҫ���ϴμ���Ƚ�
	static uchar keystate=0; ////״ֵ̬����ʼΪ0��ע�����Ǿ�̬������ֵ��ͱ��ֵ���дΪֹ
	static uchar lastkey; /////lastkey��¼�ϴμ��ʱ�ļ��룬Ҳ�Ǿ�̬����
	newkey=PINC&0X0F; /////�������PC�ڵ�4λȡֵÿ�ζ�Ҫ��ȡ
	switch(keystate)        //////����״ֵ̬���в�ͬ�Ĵ�����Ƭ������������״̬0��
	{
	case 0:                      /////״̬0
		if(newkey!=0x0f)       //////����м�
		{
			keystate=1;               //////�м�����״̬1
			lastkey=newkey;        /////�м����õ�ǰ�������ԭ������ȴ��´μ��
		}
		break;                          //////����޼�ֱ���������м��������������������ע���м�״ֵ̬�ѱ�
	case 1:                       ///////���ϴ��м�����ξ�ת��״̬1
		if(newkey==lastkey)   /////��ζ�ȡ�ļ�ֵ������ϴμ�¼��һ��������ȷ�ϰ�����
		{
			keyval=newkey;          /////ȡ�ü���
			keystate=2;                //////����״̬�´�Ҫת״̬2
		}
		else                       //////����������ϴβ�ͬ����ȷ�ϰ��������˲��������ϴ���Ҫ��״ֵ̬��0
			keystate=0;
		break;                   ///////����
	case 2:                 /////////״̬2
		if(newkey==0x0f)   ///////���10�������Ȼ�޼�
			keystate=0;            //////�´λص�״̬0
		break;
	}
	return keyval;      ////////���ؼ���
}
void key()
{
	uchar kkk;
	kkk=readkey();
	if(kkk==0x0d)
	{
		a++;
		if(a==10)a=0;
	}
	if(kkk==0x0e)
	{
		b++;
		if(b==10)b=0;
	}
	if(kkk==0x0b)
	{
		c++;
		if(c==10)c=0;
	}
	if(kkk==0x07)
	{
		d++;
		if(a==10)d=0;
	}
}
void main()
{
	while(1)
	{
		display();
		key();
	}
}

//void timer0() interrupt 1
//{
//	static i=0;
//	TH0=THx;TL0=TLx;
//	if(++i==20)
//	{
//	
//	}
//}


















