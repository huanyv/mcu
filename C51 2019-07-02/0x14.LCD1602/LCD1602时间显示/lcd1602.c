#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_E=P2^7;

#define count 50000
#define THx (65536-count)/256
#define TLx (65536-count)%256

#define LCD_DB P0

uint j;
uchar str[]="00:00:00";
uchar TIME[]="      TIME";

void delay(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
	for(j=0;j<10;j++);
}

void LCD_write_0(uchar dat)
{
	LCD_DB=dat;
	LCD_RS=0;
	LCD_RW=0;
	LCD_E=1;
	LCD_E=0;
	delay(1);
}

void LCD_write_1(uchar dat)
{
	LCD_DB=dat;
	LCD_RS=1;
	LCD_RW=0;
	LCD_E=1;
	LCD_E=0;
	delay(1);
}

void row(uint i)
{
	uint k;
	if(i==1)
	k=0x00;
	else
	k=0x40;
	LCD_write_0(0x80|k);
}

void LCD_init()
{
	LCD_write_0(0x38);
	delay(150);
	LCD_write_0(0x38);
	LCD_write_0(0x0c);
	LCD_write_0(0x06);
	LCD_write_0(0x01);
	delay(200);
}

int main()
{
	uchar i=0,i1=0,i2;
    TH0=THx;TL0=TLx;
    ET0=1;EA=1;TR0=1; TMOD=0x01; 
	LCD_init();
    while(1)
    {
		row(1);
		for(i1=0;TIME[i1]!='\0';i1++)
		{
			LCD_write_1(TIME[i1]);
            delay(10);
		}
        row(2);
		for(i2=0;i2<4;i2++)
			  LCD_write_1(' ');
        for(i=0;str[i]!='\0';i++)
        {
            LCD_write_1(str[i]);
            delay(10);	
        }
	delay(5);
	}
	return 0;
}

void time0() interrupt 1
{
    TH0=THx;TL0=TLx;
    if(++j==20)
    {
        j=0;
        str[7]++;
        if(str[7]==':')
        {
            str[7]='0';
            str[6]++;
            if(str[6]=='6')
            {
                str[6]='0';
                str[4]++;
                if(str[4]==':')
                {
                    str[4]='0';
                    str[3]++;
                    if(str[3]=='6')
                    {			 
                        str[3]='0';
                        str[1]++;        
                        if(str[0]=='2')
                        {
                            if(str[1]=='4')
                            {
                                str[1]='0';
                                str[0]='0';
                            }
                        }
                        else
                        {
                            if(str[1]==10)
                            {
                            str[1]='0';
                            str[0]++;
                            }
                        }
                    }
                }
            }
        }
    }
}