#ifndef _LCD12864_H_
#define _LCD12864_H_



sbit LCD_RW  = P2^1;
sbit LCD_EN  = P2^0;
sbit LCD_RS  = P2^2;
sbit LCD_PSB = P2^3;


#define LCD_DATA    P0



void LCD_WriteData(unsigned char dat);
void LCD_WriteCmd(unsigned char dat);
void LCD_Pos(unsigned char X,unsigned char Y);
void delay(unsigned int i);
void LCD_Init();






#endif




