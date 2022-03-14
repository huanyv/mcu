#include<reg52.h>
#include<lcd1602.h>
#include<ds1302.h>
//				  01234567
uchar time_lcd[]="00:00:00";
//				  0123456789
uchar date_lcd[]="2018-01-01";							  //11
uchar week_lcd[][6]={{"000"},{"Mon."},{"Tues."},{"Wed."},{"Thur."},{"Fri."},{"Sat."},{"Sun."}};

////             年   月   日   时   分   秒  星期
//uchar time[]={0x18,0x12,0x15,0x20,0x44,0x00,0x06};
//                0    1    2    3    4    5    6

void time_and_date()
{
	ds1302_read_time();

	time_lcd[0]=time[3]/16+'0';
	time_lcd[1]=time[3]%16+'0';
	time_lcd[3]=time[4]/16+'0';
	time_lcd[4]=time[4]%16+'0';
	time_lcd[6]=time[5]/16+'0';
	time_lcd[7]=time[5]%16+'0';

	date_lcd[2]=time[0]/16+'0';
	date_lcd[3]=time[0]%16+'0';
	date_lcd[5]=time[1]/16+'0';
	date_lcd[6]=time[1]%16+'0';
	date_lcd[8]=time[2]/16+'0';
	date_lcd[9]=time[2]%16+'0';
}

int main()
{
	uint i,j,k,g;
	lcd1602init();
	ds1302_init();
//	lcd1602_X_Y(2,1,'a');
	while(1)
	{	
		j=4;k=0;g=11;
		 
		time_and_date();

		for(i=0;time_lcd[i]!='\0';i++)
		{
			lcd1602_X_Y(2,j++,time_lcd[i]);
			delay(100);
		}
		for(i=0;date_lcd[i]!='\0';i++)
		{
			lcd1602_X_Y(1,k++,date_lcd[i]);
			delay(100);
		}
		for(i=0;week_lcd[time[6]][i]!='\0';i++)
		{
			lcd1602_X_Y(1,g++,week_lcd[time[6]][i]);
			delay(100);
		}
	}
	return 0;
}