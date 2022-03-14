#include "reg52.h"
#include "intrins.h"
#include <stdio.h>
#include <stdlib.h>
#include <game.h>

uint time_count=0;
uchar code table1[7][8]={{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
							 					 {0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00},
									 			 {0x00,0x06,0x06,0x00,0x00,0x60,0x60,0x00},
												 {0x03,0x03,0x00,0x18,0x18,0x00,0xC0,0xC0},
												 {0x00,0x66,0x66,0x00,0x00,0x66,0x66,0x00},
												 {0xC3,0xC3,0x00,0x18,0x18,0x00,0xC3,0xC3},
												 {0x00,0xDB,0xDB,0x00,0x00,0xDB,0xDB,0x00}};
void delay(uint i)
{
	while(i--);
}
void hc595(uchar dat)
{
	uchar i=0;
	stcp=0;
	for(i=0;i<8;i++)
	{
		shcp=0;
		ds=dat>>7;
		dat=dat<<1;
		shcp=1;
	}
	stcp=1;
}
void state_switch(void)
{
	uchar i=0,j=6;
	srand(time_count);
	while(j--)
	{
		P0=0xfe;
		for(i=0;i<8;i++)
		{
			
			hc595(table1[(rand()%5)+1][i]);
			delay(100);
			hc595(0x00);
			P0=P0<<1|0x01;
		}
		delay(4000);
	}
}
void display()
{

	uchar i=0;
	static bit flag_song=0;
	static uchar count=0;
	if(flag_song==0&&k1==0)
	{
		delay(1500);
		if(k1==0)
		{
			flag_song=1;
			srand(time_count);
			count = (rand()%6)+1;
			state_switch();
		}
	}
	if(k1==1)
	{
		flag_song=0;
	}
	P0=0xfe;
	for(i=0;i<8;i++)
	{
		hc595(table1[count][i]);
		delay(50);
		hc595(0x00);
		P0=P0<<1|0x01;
	}
}
void time_init(void)
{
	TMOD=0x02;
	TH0=200;
	TL0=200;
	EA=1;
	ET0=1;
	TR0=1;
}
void game(void)
{
	time_init();
	while(1)
	{
		display();
	}
}
void time0(void) interrupt 1
{
	static uint i=0;
	if(++i==500)
	{
		i=0;
		time_count++;
		if(time_count==30000)
		{
			time_count=0;
		}
	}
} 









