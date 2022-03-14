#include"reg52.h"
void delay(unsigned int i)
{
    unsigned char a,b,c;
    while(i--) {
        for(c=205; c>0; c--)
            for(b=116; b>0; b--)
                for(a=9; a>0; a--);
    }
}
void main(void) {
    while(1) {
        P2 = 0xff;
        delay(1);
        P2 = 0x00;
        delay(1);
    }
}












