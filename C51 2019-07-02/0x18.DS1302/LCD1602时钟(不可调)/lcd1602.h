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

void delay(uint i_1);
void lcd1602write_0(uchar dat);
void lcd1602write_1(uchar dat);
void lcd1602_X_Y(uchar x,uchar y,uchar dat);
void lcd1602init();




#endif