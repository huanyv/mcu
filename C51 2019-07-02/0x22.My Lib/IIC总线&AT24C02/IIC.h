#ifndef _IIC_H_
#define _IIC_H_

#include<reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

sbit scl=P2^1;
sbit sda=P2^0;

/*****************延时5us************/
void delay5us();   //误差 0us

/***************开始信号*************/
void start();

/***************停止信号*************/
void iic_stop();

/**************应答信号*************/
void respons();

/**************初始化*************/
void init();

/***************写一个字节**********/
void write_byte(uchar date);

/***************读一个字节************/
uchar read_byte();

/*****************写数据*******************/
void write_add(uchar addr,uchar date);

/******************读数据*******************/
uchar read_addr(uchar addr);


#endif