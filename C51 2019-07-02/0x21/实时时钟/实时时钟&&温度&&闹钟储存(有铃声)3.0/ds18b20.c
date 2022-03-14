#include<ds18b20.h>

void delay_ds18b20(uint iii)
{
	while(iii--);
}

void ds18b20_init()
{	  
	uchar x=0;
	DQ=0;
	delay_ds18b20(80);
	DQ=1;
	delay_ds18b20(10);
	x=DQ;
	delay_ds18b20(5);
}

uchar ds18b20_read()
{	  
	uchar i,dat=0;
	for(i=0;i<8;i++)
	{
		dat=dat>>1;
		DQ=0;
		DQ=1;
		if(DQ)
		dat=dat|0x80;
		delay_ds18b20(5);
		DQ=1;
		
	}
	return dat;		   
}

void ds18b20_write(uchar dat)
{		
	uchar i;
	for(i=0;i<8;i++)
	{
		DQ=0;
		DQ=dat & 0x01;
		delay_ds18b20(5);
		DQ=1;
		delay_ds18b20(1);
		dat=dat>>1;
	}
	DQ=1;
	delay_ds18b20(5);	
}

int ds18b20_read_temp()
{	
	uchar h=0,l=0;
	int sum=0;

	ds18b20_init();
	delay_ds18b20(10);
	ds18b20_write(0xcc);
	ds18b20_write(0x44);
	delay_ds18b20(200);

	ds18b20_init();
	delay_ds18b20(10);
	ds18b20_write(0xcc);
	ds18b20_write(0xbe);
	l=ds18b20_read();
	h=ds18b20_read();
	sum=h;
	sum=sum<<8;
	sum=sum|l;

	return sum;			
}