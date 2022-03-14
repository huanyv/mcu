#include<ds1302.h>
#include<intrins.h>

uchar code writedate[]={0x8c,0x88,0x86,0x84,0x82,0x80,0x8a};
uchar code readdate[]={0x8d,0x89,0x87,0x85,0x83,0x81,0x8b};
//             年   月   日   时   分   秒  星期
uchar time[]={0x18,0x12,0x15,0x20,0x44,0x00,0x06};


void ds1302write(uchar add,uchar dat)
{  
	uchar i;
	CE=0;
	_nop_();
	SCLK=0;
	_nop_();
	CE=1;
	_nop_();
	for(i=0;i<8;i++)
	{
		IO=add & 0x01;
		add=add>>1;
		SCLK=1;
		_nop_();
		SCLK=0;
		_nop_();
	}
	for(i=0;i<8;i++)
	{
		IO=dat & 0x01;
		dat=dat>>1;
		SCLK=1;
		_nop_();
		SCLK=0;
		_nop_();
	}
	CE=0;
	_nop_();
}

uchar ds1302read(uchar add)
{	
	uchar i,dat;
	CE=0;
	_nop_();
	SCLK=0;
	_nop_();
	CE=1;
	_nop_();
	for(i=0;i<8;i++)
	{
		IO=add & 0x01;
		add=add>>1;
		SCLK=1;
		_nop_();
		SCLK=0;
		_nop_();
	}
	for(i=0;i<8;i++)
	{
		if(IO)
		dat=dat | 0x80;
		dat=dat>>1;			   
		SCLK=0;
		_nop_();
		SCLK=1;
		_nop_();
	}
	CE=0;
	_nop_();
	SCLK=1;
	_nop_();
	IO=0;
	_nop_();
	IO=1;
	_nop_();
	return dat;		 
}

void ds1302_init()
{
	uchar i;
	ds1302write(0x8e,0x00);
	for(i=0;i<7;i++)
	{
		ds1302write(writedate[i],time[i]);
	} 
	ds1302write(0x8e,0x80);
}

void ds1302_read_time()
{
	uchar i;
	for(i=0;i<7;i++)
	{
		time[i]=ds1302read(readdate[i]);
	}
}