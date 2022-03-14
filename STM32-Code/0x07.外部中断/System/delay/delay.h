#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f10x.h"

//��ʼ���ӳ�
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
#define   Delay_Init()       SysTick->CTRL |= 0xFFFFFFFB 	//CTRL�Ĵ��� bit2  ѡ���ⲿʱ�� HCLK/8


void delay_us(uint32_t us);
void delay_ms(uint16_t ms);
void delay_s(uint16_t s);

#endif





























