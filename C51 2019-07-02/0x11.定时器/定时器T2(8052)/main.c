#include"stc89c5xrc.h"
typedef unsigned char uchar;
typedef unsigned int uint;

sbit A38=P2^2;
sbit B38=P2^3;
sbit C38=P2^4;

#define count 50000
#define THx (65536-count)/256;
#define TLx (65536-count)%256;

uchar sec=0;
uchar table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void timer2_init(void){
	EXEN2=0;//�ر�T2EX������
	C_T2=0;//ʹ�ö�ʱ������
	RCLK=TCLK=0;//
	TR2=1;//������ʱ��
	EA=1;ET2=1;//���ж�

	RCAP2L=TL2=TLx;//�Ͱ�λ
	RCAP2H=TH2=THx;//�߰�λ
}

void main(void){
	A38=0;
	B38=0;
	C38=0;
	timer2_init();
	while(1){
	
	
		P0=table[sec];
		
		
	}
}
void timer2() interrupt 5
{
	static uchar i=0;
	TF2=0;//��� �� ��־λ
	if(++i==20)
	{
		i=0;
		sec++;
		if(sec==10)
		{
			sec=0;
		}
	}
}





















