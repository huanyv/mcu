#include "18b20.h"
#include "delay.h"

void GPIO_18B20_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
}
void GPIO_18B20_Init_Out() {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA ,&GPIO_InitStructure);
}
void GPIO_18B20_Init_In() {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15;
	GPIO_Init(GPIOA ,&GPIO_InitStructure);
}
void DS18B20_Init() {
	uint8_t x = 0;
	uint8_t i = 0;
	GPIO_18B20_Init_Out();
	DQ = 1;
	delay_us(80);
	DQ = 0;
	delay_us(800);
	DQ = 1;
	delay_us(20);
	GPIO_18B20_Init_In();
	x = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);//��ʼ���ɹ� �� �� 0
	while((x==1)&&(i<255)) {
		i++;
		delay_us(1);
	}
}
void DS18B20_Write(uint8_t dat) {
	uint8_t i;
	GPIO_18B20_Init_Out();
	for(i=0;i<8;i++) {
		DQ = 0;
		DQ = dat & 0X01;
     		delay_us(70);
		DQ = 1;
		dat = dat >> 1;
	}
	delay_us(70);
}
uint8_t DS18B20_Read() {
	uint8_t i,dat;
	
	for(i=0;i<8;i++) {
		dat = dat>>1;
		
		GPIO_18B20_Init_Out();//����DQǰҪ��IO��Ϊ��� ģʽ  �����죩��Ҫ
		DQ   = 0;delay_us(5);
		DQ   = 1;delay_us(5);
		
		GPIO_18B20_Init_In();//��ȡ����������ǰҪ������Ϊ����ģʽ ���������룩��Ҫ
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15) == 1)
			dat |= 0x80;
		delay_us(50);
	}
	return dat;
}
int Read_Temp(void) {
	uint8_t TL,TH;
	int TEMP;
	
	DS18B20_Init();
	delay_ms(1);
	DS18B20_Write(0xcc);
	DS18B20_Write(0x44);
	delay_ms(2);
	
	DS18B20_Init();
	delay_ms(1);
	DS18B20_Write(0xcc);
	DS18B20_Write(0xbe);
	
	TL = DS18B20_Read();
	TH = DS18B20_Read();
	
	TEMP=TH;
	TEMP <<= 8;
	TEMP |= TL;
	return TEMP;
}













