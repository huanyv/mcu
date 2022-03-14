#include<xpt2046.h>
#include<intrins.h>

void delay(uint i)
{
	while(i--);
}

void write_date(uchar dat)
{
	uchar i;
	DCLK=0;					 //在  开始  发送数据  前  应设置好  时钟线  的  初始状态
	for(i=0;i<8;i++)
	{
		DIN=dat>>7;
		dat=dat<<1;
		DCLK=0;			   // 时钟线在   上升沿
		DCLK=1;			   // 会发送 （写）  数据
	}
}
uint read_date()
{
	uint i,dat=0;			//dat要赋初值    每次循环都为  一开始  为   0
	DCLK=0;
	for(i=0;i<12;i++)
	{
		dat=dat<<1;
		DCLK=1;			 //		时钟线在  下降沿 
		DCLK=0;			 //		会接收 （读）  数据 
		dat=dat|DOUT;
	}
	return dat;	
}

uint xpt2046(uchar t)
{
	uint AD;
	DCLK=0;
	CS=0;	
	write_date(t);
//	delay(1);		 //延时不要太大
/*	DCLK=1;
	_nop_();
	_nop_();
	DCLK=0;
	_nop_();
	_nop_();          */	
	AD=read_date();
	CS=1;
	return AD;
}