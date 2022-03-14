#ifndef _GAME_H_
#define _GAME_H_

#define uchar unsigned char
#define uint unsigned int


sbit shcp=P3^6;
sbit stcp=P3^5;
sbit ds=P3^4;
sbit k1=P3^1;


void delay(uint i);
void state_switch(void);
void hc595(uchar dat);
void display();
void time_init(void);
void game(void);
void time0(void);



#endif