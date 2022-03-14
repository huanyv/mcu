#include "display.h"
#include "keyboard.h"
#include "stm32f10x.h"

uint8_t table1[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d, 
					0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; //共阴数码管 段码
uint8_t dat = 0;
					
void Display_GPIO_Init(void) {
	GPIO_InitTypeDef GPIOinit;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIOinit.GPIO_Pin   = GPIO_Pin_All;
	GPIOinit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOinit.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIOinit);
}

void display(void) {
	uint8_t key;
	
	key = Read_Key();
	
#if 0
	
	if(key == 1) {                //矩阵键盘控制
		dat++;if(dat == 10)dat = 0; //矩阵键盘控制
	}                             //矩阵键盘控制
	if(key == 2) {                //矩阵键盘控制
		dat--;if(dat == 255)dat = 9;//矩阵键盘控制
	}                             //矩阵键盘控制
	
#else
	
	if(key != 0) {         //数码管显示键值
		dat = key-1;         //数码管显示键值
	}                      //数码管显示键值
	
#endif
	
	C38 = 0; B38 = 0; A38 = 0;
	
	GPIO_Write(GPIOB,GPIO_ReadOutputData(GPIOB) & 0X00FF);
	GPIO_Write(GPIOB,GPIO_ReadOutputData(GPIOB) | (table1[dat]<<8));

}



