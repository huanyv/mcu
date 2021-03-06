#ifndef __OLED_I2C_H
#define	__OLED_I2C_H
#include "sys.h"

#define     OLED_ADDR   	            0x78   //通过调整0R电阻,屏可以0x78和0x7A两个地址 -- 默认0x78

//User FONT Lib  #define
/******************BEGIN************************/

#define     CN_16X16_ENABLE           1
                                      
#define     ASCII_12x14_ENABLE        0
                                      
#define     ASCII_6X8_8x16_ENABLE     1
                                      
#define     BMP_ENABLE                0
                                      
#define     ASCII_16X32_ENABLE        1

/*******************END*************************/






void WriteCmd(unsigned char I2C_Command);
void WriteDat(unsigned char I2C_Data);
void OLED_Init(void);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);

void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);


void OLED_ShowCN(u8 x,u8 y,u8 no,const uint8_t ch[][32]);
void OLED_Show16x32(uint8_t x,uint8_t y,uint8_t ch[]);
void OLED_Show12x24(uint8_t x,uint8_t y,uint8_t ch[]);



#endif /* __OLED_I2C_H */









