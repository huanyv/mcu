#include "i2c.h"
#include "delay.h"



void GPIO_I2C_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}


void GPIO_I2C_Out(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
void GPIO_I2C_In(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
void I2C_Start(void) {
	GPIO_I2C_Out();
	sda = 1;
	delay_us(5);
	scl = 1;
	delay_us(5);
	sda = 0;
	delay_us(5);
	scl = 0;
	delay_us(5);
}
void I2C_Stop(void) {
	GPIO_I2C_Out();
	sda = 0;
	delay_us(5);
	scl = 1;
	delay_us(5);
	sda = 1;
	delay_us(5);
	scl = 0;
	delay_us(5);
}

void I2C_Respons(void) {
	uint32_t i =0;
	scl = 1;
	delay_us(5);
	GPIO_I2C_In();
	while((sda_in == 1) && (i<1000))
		i++;
	scl = 0;
	delay_us(5);
}
void I2C_Write_Byte(uint8_t dat) {
	uint8_t i , t;
	GPIO_I2C_Out();
	t = dat;
	for(i=0;i<8;i++) {
		scl = 0;
		delay_us(5);
		sda = (t>>7);
		scl = 1;
		delay_us(5);
		t = t<<1;
	}
	scl = 0;
	delay_us(5);
	sda = 1;
	delay_us(5);
}
uint8_t I2C_Read_Byte(void) {
	uint8_t i , k;
	scl = 0;
	delay_us(5);
	sda = 1;
	delay_us(5);
	GPIO_I2C_In();
	for(i=0;i<8;i++) {
		scl = 1;
		delay_us(5);
		k = (k<<1) | sda_in;
		scl = 0;
		delay_us(5);
	}
	return k;
}










