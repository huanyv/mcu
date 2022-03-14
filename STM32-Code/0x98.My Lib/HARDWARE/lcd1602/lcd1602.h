#ifndef _LCD1602_H_
#define _LCD1602_H_
#include "sys.h"

#define LCD_RS PBout(6)
#define LCD_RW PBout(5)
#define LCD_EN PBout(7)

void LCD_Write_Cmd(uint8_t cmd);
void LCD_Write_Dat(uint8_t dat);
void LCD_X_Y(uint8_t x,uint8_t y,uint8_t dat) ;
void LCD_Init(void);
void zidingyi(uint8_t (*s)[8],uint8_t len,uint8_t count);
#endif
