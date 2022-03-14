#include "keyboard.h"
#include "delay.h"
#include "sys.h"

void key_init1(void){
	GPIO_InitTypeDef GPIOinit;

	GPIOinit.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIOinit.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOinit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOinit);
	
	GPIOinit.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIOinit.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIOinit);
}
void key_init2(void){
	GPIO_InitTypeDef GPIOinit;
	
	GPIOinit.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIOinit.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOinit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOinit);
	
	GPIOinit.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIOinit.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIOinit);
}

uint8_t Read_Key(void) {
	uint8_t key_count;//返回键值
	static uint8_t key_song = 0;//松手检测变量
	
	key_init2();//PA0`3至为输入，PA4`7至为输出
	GPIO_Low8BitWrite(GPIOA,0X0F);//PA0`3至为高电平，PA4`7至为低电平

	if((key_song == 0)&&((GPIO_ReadInputData(GPIOA)&0x00ff) != 0x000f)) {
		delay_ms(15);
		key_song = 1;
		switch(GPIO_ReadInputData(GPIOA)&0x00ff) {//确定第几列响应
			case 0x07:key_count = 1;break;
			case 0x0b:key_count = 2;break;
			case 0x0d:key_count = 3;break;
			case 0x0e:key_count = 4;break;
		}
		
		key_init1();//PA4`7至为输入，PA0`3至为输出
    GPIO_Low8BitWrite(GPIOA,0XF0);//低八位电平翻转

		switch(GPIO_ReadInputData(GPIOA)&0x00ff) {//确定第几行响应
			case 0x70:key_count = key_count;   break;
			case 0xb0:key_count = key_count+4; break;
			case 0xd0:key_count = key_count+8; break;
			case 0xe0:key_count = key_count+12;break;
		}
	}
	if((GPIO_ReadInputData(GPIOA)&0x00ff) == 0x000f) {
		key_song = 0;
	}
	return key_count;
}
















