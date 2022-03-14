#include<iic.h>

/*****************��ʱ5us************/
void delay5us()   //��� 0us
{
    unsigned char a;
    for(a=1;a>0;a--);
}

/***************��ʼ�ź�*************/
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

/***************ֹͣ�ź�*************/
void iic_stop()
{
	sda=0;
	delay5us();
	scl=1;
	delay5us();
	sda=1;
	delay5us();
}

/**************Ӧ���ź�*************/
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

/**************��ʼ��*************/
void init()
{
	sda=1;
	delay5us();
	scl=1;
	delay5us();
}

/***************дһ���ֽ�**********/
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

/***************��һ���ֽ�************/
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

/*****************д����*******************/
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

/******************������*******************/
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