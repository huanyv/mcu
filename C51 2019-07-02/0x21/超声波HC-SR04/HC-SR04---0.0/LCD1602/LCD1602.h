#ifndef _LCD1602_H_
#define _LCD1602_H_
#include "hcsr04.h"
#include<reg52.h>



sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_E=P2^7;

#define LCD_DB P0

void LCD_write_0(uchar dat);//д��ָ��
void LCD_write_1(uchar dat);//��������  
void LCD_Init();//��ʼ��

void LCD_X_Y(uchar x,uchar y,uchar date);//�Զ�����ʾ  λ��

void zidingyi(uchar (*s)[8],uint j,uint j_1);//�Զ�����ʾ  �ַ�

#endif
