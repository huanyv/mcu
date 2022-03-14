#include<ds18b20.h>
void delay(uint i)
{
    while(i--);
}
void DS18B20_init()
{
	uchar x=0;
	DQ=1;
	delay(8);
	DQ=0;
	delay(80);
	DQ=1;
	delay(10);
	x=DQ;
	delay(5);  
}
uchar DS18B20_read()
{
    uchar i,t=0,j=0;
    for(i=0;i<8;i++)
    {
        DQ=0;
        t=t>>1;
        DQ=1;
        if(DQ)
        t=t|0x80;
        delay(5);
		DQ=1;
    }
    return t;  
}

void DS18B20_write(uchar dat)
{
    uchar i;
    for(i=0;i<8;i++)
    {
        DQ=0;
        DQ=dat&0x01;
        delay(5);
        DQ=1;
        dat=dat>>1;
    }
    delay(5);	 
}
uint readc()
{
    uchar a=0,b=0;
    uint c=0;
    DS18B20_init();
	delay(10);
    DS18B20_write(0xcc);
    DS18B20_write(0x44);
    delay(200);
    DS18B20_init();
	delay(10);
    DS18B20_write(0xcc);
    DS18B20_write(0xbe);
    b=DS18B20_read();
    a=DS18B20_read();
    c=a;
    c=c<<8;
    c=c|b;
	return c;
}