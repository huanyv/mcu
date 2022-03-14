#include<reg52.h>
#include<lcd1602.h>
#include <zhuanhuan.h>

//typedef unsigned char uchar;
//typedef unsigned int uint;


uchar day=5,month=1,year=19;
//uchar day1,month1,year1;

void delay(uint i)
{
	while(i--);
}
void display()
{//				  0123456789
	uchar date[]="2018-01-01";
	uchar str[8]="";
	uchar i=0;
	date[2]=year/10+'0';
	date[3]=year%10+'0';
	date[5]=month/10+'0';
	date[6]=month%10+'0';
	date[8]=day/10+'0';
	date[9]=day%10+'0';
	for(i=0;date[i]!='\0';i++)//阳历显示
	{
		LCD_X_Y(1,i,date[i]);
		delay(10);
	}
	zhuan_huan(year,month,day,str);
	for(i=0;str[i]!='\0';i++)//阴历显示
	{
		LCD_X_Y(2,i,str[i]);
		delay(10);
	}
	LCD_write_0(0x80+15);
	LCD_write_1('0');
}
void main()
{
	LCD_init();
	while(1)
	{
		display();
	}
}