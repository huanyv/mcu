#ifndef _LCD1602_H_
#define _LCD1602_H_

#include<reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_E=P2^7;

#define LCD_DB P0

void delay_1(uint x);
void LCD_write_0(uchar dat);//д��ָ��
void LCD_write_1(uchar dat);//��������  
void row(uint i);//�Զ�����ʾ��
void LCD_init();//��ʼ��
void LCD_X_Y(uchar x,uchar y,uchar date);//�Զ�����ʾ  λ��
void zidingyi(uchar *s,uint j);//�Զ�����ʾ  �ַ�

#endif