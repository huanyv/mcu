#ifndef __OLED_H
#define __OLED_H
#include <reg52.h>

#define      uint8_t          unsigned char
#define      uint16_t         unsigned int

#define      OLED_ADDR        0x78



#define      ASCII_8x16_ENABLE         1

#define      ASCII_16x32_ENABLE        0






void delay_ms(uint16_t i);
void OLED_Init(void);
void OLED_Fill(uint8_t dat);
void OLED_CLS(void);
void Showstr8x16(uint8_t x,uint8_t y,uint8_t ch[]);
void Showstr16x32(uint8_t x,uint8_t y,uint8_t ch[]);

#endif /* __OLED_H */