#ifndef _LCD1602_H_
#define _LCD1602_H_
#include "hcsr04.h"
#include<reg52.h>



sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_E=P2^7;

#define LCD_DB P0

void LCD_write_0(uchar dat);//写入指令
void LCD_write_1(uchar dat);//定入数据  
void LCD_Init();//初始化

void LCD_X_Y(uchar x,uchar y,uchar date);//自定义显示  位置

void zidingyi(uchar (*s)[8],uint j,uint j_1);//自定义显示  字符

#endif
