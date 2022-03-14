#include"reg52.h"

#define    LED_Direction      1

#define    LED                P2

void delay(unsigned int i) {
    unsigned char a;
    while(i--) {
        for(a = 0; a<123; a++);
    }
}
void main(void) {

    unsigned char i , j;
    unsigned char LED_H        = 0;
    unsigned char LED_L        = 0;
    unsigned char LED_STOP_L   = 0xff;
    unsigned char LED_STOP_H   = 0xff;
    unsigned char LED_STOP_AND = 0xff;

    for(i = 0; i<4; i++) {
        LED_H = 0x7f;
        LED_L = 0xfe;
        for(j = 4; j > i; j--) {
					
#if     LED_Direction
					
            LED  = LED_H & LED_L & LED_STOP_AND;//向内
					
#else
					
            LED = ((LED_H & LED_L & LED_STOP_AND) <<4) | ((LED_H & LED_L & LED_STOP_AND) >>4);//向外
					
#endif
					
            LED_H = LED_H>>1 | 0x80;
            LED_L = LED_L<<1 | 0x01;

            delay(500);
        }
        LED_STOP_L >>= 1;
        LED_STOP_H <<= 1;

        LED_STOP_AND = (LED_STOP_L >>4) | (LED_STOP_H <<4);
    }
    while(1);
}












