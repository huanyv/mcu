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
sbit LCD_EN=P2^7;

#define LCD_DB P0

void delay_lcd(uint iii);
void lcd1602_write_0(uchar dat);
void lcd1602_write_1(uchar dat);
void lcd_zidingyi(uchar (*s)[],uchar i_1,uchar i_2);
void lcd1602_X_Y(uchar x,uchar y,uchar dat);
void lcd1602_init();




#endif