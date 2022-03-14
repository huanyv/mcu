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

/*****************��ʱ5us************/
void delay5us();   //��� 0us

/***************��ʼ�ź�*************/
void start();

/***************ֹͣ�ź�*************/
void iic_stop();

/**************Ӧ���ź�*************/
void respons();

/**************��ʼ��*************/
void init();

/***************дһ���ֽ�**********/
void write_byte(uchar date);

/***************��һ���ֽ�************/
uchar read_byte();

/*****************д����*******************/
void write_add(uchar addr,uchar date);

/******************������*******************/
uchar read_addr(uchar addr);


#endif