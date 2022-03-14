#include<iic.h>

/*****************延时5us************/
void delay5us()   //误差 0us
{
    unsigned char a;
    for(a=1;a>0;a--);
}

/***************开始信号*************/
void start()
{
	sda=1;
	delay5us();
	scl=1;
	delay5us();
	sda=0;
	delay5us();
	scl=0;
	delay5us();
}

/***************停止信号*************/
void iic_stop()
{
	sda=0;
	delay5us();
	scl=1;
	delay5us();
	sda=1;
	delay5us();
}

/**************应答信号*************/
void respons()
{
	uchar i;
	scl=1;
	delay5us();
	while((sda==1)&&(i<255))
		i++;
	scl=0;
	delay5us();
}

/**************初始化*************/
void init()
{
	sda=1;
	delay5us();
	scl=1;
	delay5us();
}

/***************写一个字节**********/
void write_byte(uchar date)
{
	uchar i,t;
	t=date;
	for(i=0;i<8;i++)
	{
		t=t<<1;
		scl=0;
		delay5us();
		sda=CY;
		delay5us();
		scl=1;
		delay5us();
	}
	scl=0;
	delay5us();
	sda=1;
	delay5us();
}

/***************读一个字节************/
uchar read_byte()
{
	uchar i,k;
	scl=0;
	delay5us();
	sda=1;
   	delay5us();
	for(i=0;i<8;i++)
	{
		scl=1;
		delay5us();
		k=(k<<1)|sda;
		scl=0;
		delay5us();
	}
	return k;
}

/*****************写数据*******************/
void write_add(uchar addr,uchar date)
{
	start();
	write_byte(0xa0);
	respons();
	write_byte(addr);
	respons();
	write_byte(date);
	respons();
	iic_stop();
}

/******************读数据*******************/
uchar read_addr(uchar addr)
{
	uchar date;
	start();
	write_byte(0xa0);
	respons();
	write_byte(addr);
	respons();
	start();
	write_byte(0xa1);
	respons();
	date=read_byte();
	iic_stop();
	return date;
}