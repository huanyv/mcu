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
    uchar i,t=0;
    for(i=0; i<8; i++)
    {
        t=t>>1;
        DQ=0;
        DQ=1;
        if(DQ == 1)
            t=t|0x80;
				 
        delay(5);
    }
    return t;
}

void DS18B20_write(uchar dat)
{
    uchar i;
    for(i=0; i<8; i++)
    {
        DQ=0;
        DQ=dat&0x01;
        delay(5);
        DQ=1;
        dat=dat>>1;
    }
    delay(5);
}
int readc()
{
    uchar TL=0,TH=0;
    int TEMP=0;
    DS18B20_init();
    delay(10);
    DS18B20_write(0xcc);
    DS18B20_write(0x44);
    delay(200);
    DS18B20_init();
    delay(10);
    DS18B20_write(0xcc);
    DS18B20_write(0xbe);
    TH=DS18B20_read();
    TL=DS18B20_read();
    TEMP=TL;
	TEMP=TEMP<<8;
    TEMP=TEMP | TH;
    return TEMP;
}