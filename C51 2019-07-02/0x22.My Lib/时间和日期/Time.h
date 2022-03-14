#ifndef _TIME_H_
#define _TIME_H_

#include<reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;

uchar seconds=0,minute=0,i=0,hour=0;
uchar month=1,dat=1;
uchar year=0,year_h=20;
uint switch1=0;	

uint leapyear()/************是否闰年************/
uint datnumber()/************判断天数************/
void time()            //时间显示 
void time&date()//时间和日期显示
void datekongzhi()/**************日期控制***************/
void timekongzhi()//时间控制


#endif