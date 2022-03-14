#include<reg52.h>
#include<lcd1602.h>
#include<xpt2046.h>

uchar volts[]="0.000V";
uchar code flag[]="VOTLS:";

#define count 50000
#define THx (65536-count)/256
#define TLx (65536-count)%256

uint j,seconds=0,temp=0; 
bit flag_1;

void xpt2046_1()
{
	uint volt;
	float tp;
	if(flag_1)
	{	  
		flag_1=0;
		temp=xpt2046(0x94);	
//		temp=xpt2046(0xd4);		 热敏
//		temp=xpt2046(0xa4);			  光敏
//		temp=xpt2046(0xe4);				   自定
	}			
	
	tp=5.0*(float)temp/4096.0;
	volt=tp*1000+0.5;

	volts[0]=volt/1000+'0';
	volts[2]=volt/100%10+'0';
	volts[3]=volt/10%10+'0';
	volts[4]=volt%10+'0';
}

void time0init()
{
	TMOD=0x01;
	TH0=THx;TL0=TLx;
	EA=1;ET0=1;
	TR0=1;
}

int main()
{
	uchar i=0,k=5;
	time0init();
	LCD_init();
	for(i=0;i<6;i++)
	{
		LCD_X_Y(1,k++,flag[i]);
		delay(10);
	}
	while(1)
	{
		xpt2046_1();
		k=5;
		for(i=0;i<6;i++)
		{
			LCD_X_Y(2,k++,volts[i]);
			delay(100);
		}
	}
}

void timr0() interrupt 1
{
	TH0=THx;TL0=TLx;
	if(++j==20)
	{	
		flag_1=1;
		j=0;
		seconds++;
		
		if(seconds==60)
		{
			seconds=0;
		}
	}
}