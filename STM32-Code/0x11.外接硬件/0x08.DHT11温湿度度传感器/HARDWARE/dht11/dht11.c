#include "dht11.h"
#include "delay.h"
	

static void DHT11_GPIO_Out(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = DHT11_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
static void DHT11_GPIO_In(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin   = DHT11_PIN;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
static void DHT11_START(void) {
	DHT11_GPIO_Out();
	DHT11_IO = 1;
	delay_us(10); // ���п���
	DHT11_IO = 0;
	delay_ms(20); //   18 ms�ĵ͵�ƽ 
	DHT11_IO = 1;
	delay_us(30); // 20~40us�ĸߵ�ƽ 
}

static uint8_t Receive_DHT11(void) {
	uint8_t i;
	uint8_t dat,temp;
	DHT11_GPIO_In();
	for(i=0;i<8;i++) {
		while(DHT11_IO_IN == 0);//�ȴ�50us�ĵ͵�ƽ��ʼ�źŽ���
		delay_us(30);    //��ʼ�źŽ�������ʱ26us-28us
		temp=0;   //���ʱ��Ϊ26us-28us ���ʾ���յ�����Ϊ'0'
		if(DHT11_IO_IN==1)
			temp=1;//���ʱ�䳬��26us-28us ���ʾ�յ�������Ϊ'1'
		while(DHT11_IO_IN == 1);//�ȴ������źŸߵ�ƽ�� '0'Ϊ26us-28us��'1'Ϊ70us
		dat<<=1;//�����յ��������λ����
		dat|=temp;
	}
	return dat;
}
void Receive_DATA(Temperature_AND_Humidity *Temperature_AND_humidity_Structure) //��������
{
	uint8_t R_H,R_L,T_H,T_L,check;          //����׼��У��洢��ʪ�ȵı���
	uint8_t i;

	DHT11_START();//��ʼ�źų�ʼ��
	DHT11_IO=1;   //������Ϊ����  �жϴӻ�DHT11����Ӧ�ź�     
	DHT11_GPIO_In(); // ׼�������ź�
	if(DHT11_IO_IN == RESET) //�ж��Ƿ�����Ӧ�ź�
	{
		i = 0;
		while((DHT11_IO_IN == 0)&&(i<100)) {//�ȴ� DHT11 80us ����Ӧ�ź� �͵�ƽ 
			i++;
			delay_us(10);
		}
		i = 0;
		while((DHT11_IO_IN == 1)&&(i<100)) { // �ȴ�DHT ���� ��80us �ߵ�ƽ 
			i++;
			delay_us(10);
		}
		R_H   = Receive_DHT11();//ʪ������
		R_L   = Receive_DHT11();//ʪ��С��
		T_H   = Receive_DHT11();//�¶�����
		T_L   = Receive_DHT11();//�¶�С��
		check = Receive_DHT11();//У���
		DHT11_GPIO_Out();
		DHT11_IO=0;//�����е����ݽ�����ɺ󣬽��ӻ���ƽ����50us
		delay_us(50);
		DHT11_IO=1;//���ӻ���ƽ���ߣ��������״̬

		if(R_H+R_L+T_H+T_L == check)//�ж϶�ȡ��������У��λ�Ƿ���ͬ
		{
			Temperature_AND_humidity_Structure->RH = R_H;
			Temperature_AND_humidity_Structure->RL = R_L;
			Temperature_AND_humidity_Structure->TH = T_H;
			Temperature_AND_humidity_Structure->TL = T_L;
		}
		
		Temperature_AND_humidity_Structure->TEMP[0] = Temperature_AND_humidity_Structure->TH/10+48;
		Temperature_AND_humidity_Structure->TEMP[1] = Temperature_AND_humidity_Structure->TH%10+48;
		Temperature_AND_humidity_Structure->TEMP[2] = '.';
		Temperature_AND_humidity_Structure->TEMP[3] = Temperature_AND_humidity_Structure->TL/10+48;
		Temperature_AND_humidity_Structure->TEMP[4] = Temperature_AND_humidity_Structure->TL%10+48;
		Temperature_AND_humidity_Structure->TEMP[5] = 95+32;
		Temperature_AND_humidity_Structure->TEMP[6] = '\0';
		
		Temperature_AND_humidity_Structure->HUM[0] = Temperature_AND_humidity_Structure->RH/10+48;
		Temperature_AND_humidity_Structure->HUM[1] = Temperature_AND_humidity_Structure->RH%10+48;
		Temperature_AND_humidity_Structure->HUM[2] = '.';
		Temperature_AND_humidity_Structure->HUM[3] = Temperature_AND_humidity_Structure->RL/10+48;
		Temperature_AND_humidity_Structure->HUM[4] = Temperature_AND_humidity_Structure->RL%10+48;
		Temperature_AND_humidity_Structure->HUM[5] = '%';
		Temperature_AND_humidity_Structure->HUM[6] = '\0';
		
		// ֻ��ʾ��λ������ʾ����û�о�ȷ��С�����
#if   !RESET
		Temperature_AND_humidity_Structure->TEMP[2] = 95+32;
		Temperature_AND_humidity_Structure->TEMP[3] = '\0';
		
		Temperature_AND_humidity_Structure->HUM[2] = '%';
		Temperature_AND_humidity_Structure->HUM[3] = '\0';
#endif
	
	}
}









