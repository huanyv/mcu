#ifndef _LCD1602_H_
#define _LCD1602_H_
#include "sys.h"


sbit LCD_RS=P1^0;
sbit LCD_RW=P1^1;
sbit LCD_E= P1^2;

#define LCD_DB P0


void delay_1(uint x);
void LCD_write_0(uchar dat);//写入指令
void LCD_write_1(uchar dat);//定入数据  
void LCD_init();//初始化

#endif