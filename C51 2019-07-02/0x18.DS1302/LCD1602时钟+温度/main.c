#include<reg52.h>
#include<ds1302.h>
#include<ds18b20.h>			   //k4进入设置     k3调整时间
#include<lcd1602.h>

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;

uchar temper[5];
uchar time_lcd[]="00:00:00";
uchar date_lcd[]="2000-00-00";

uchar code readdate_ctrl[]={0x81,0x83,0x85,0x8b,0x87,0x89,0x8d};
uchar code writedate_ctrl[]={0x80,0x82,0x84,0x8a,0x86,0x88,0x8c};

uchar code zi[1][8]={{0x10,0x06,0x09,0x08,0x08,0x09,0x06,0x00}};

uchar code week_lcd[][6]={{"error"},{"Mon."},{"Tues."},{"Wed."},{"Thur."},{"Fri."},{"Sat."},{"Sun."}};

#define count 50000
#define thx (65536-count)/256
#define tlx (65536-count)%256

uchar flag=0;

void read_temper(int dat)
{
	float tp;
	if(dat<0)
	{
		temper[0]='-';
		dat=dat-1;
		dat=~dat;
		tp=dat;
		dat=tp*0.0625*10+0.5;	
	}
	else
	{
		temper[0]=' ';		
		tp=dat;
		dat=tp*0.0625*10+0.5;
	}

	temper[1]=dat/100%10+'0';
	temper[2]=dat/10%10+'0';
	temper[3]='.';
	temper[4]=dat%10+'0';
} 

void timer()
{
	read_time();

	time_lcd[0]=time[3]/16+'0';
	time_lcd[1]=time[3]%16+'0';
	time_lcd[3]=time[4]/16+'0';
	time_lcd[4]=time[4]%16+'0';
	time_lcd[6]=((time[5]&0x70)>>4)+'0';
	time_lcd[7]=time[5]%16+'0';

	date_lcd[2]=time[0]/16+'0';
	date_lcd[3]=time[0]%16+'0';
	date_lcd[5]=time[1]/16+'0';
	date_lcd[6]=time[1]%16+'0';
	date_lcd[8]=time[2]/16+'0';
	date_lcd[9]=time[2]%16+'0';
}

void lcd_display()
{
	uint i,j,k=0,g=10;
//******************************************* 
		for(i=0;date_lcd[i]!='\0';i++)
		{				  
			lcd1602_X_Y(1,j++,date_lcd[i]);
		}j++;
//*******************************************
		for(i=0;week_lcd[6][i]!='\0';i++)
		{
			lcd1602_X_Y(1,j++,week_lcd[time[6]][i]);
		}
//*******************************************		 
		for(i=0;time_lcd[i]!='\0';i++)
		{
			lcd1602_X_Y(2,k++,time_lcd[i]);
		}
//*******************************************		
		for(i=0;i<5;i++)
		{
			lcd1602_X_Y(2,g++,temper[i]);
		}
}


/*void time0init()
{
	TMOD=0x01;
	TH0=thx;TL0=tlx;
	TR0=1;EA=1;ET0=1;
}	  */

void stop()
{
	EA=1;EX0=1;IT0=1;
	EX1=1;IT1=1;
}

void ctrltime()
{
	uchar temp;
	if(flag==1)
	{
		lcd1602_write_0(0xc0+7);
		lcd1602_write_0(0x0f);			//光标到秒位置

		ds1302_write(0x8e,0x00);		 //时
		temp=ds1302_read(0x81);			 //间
		ds1302_write(0x80,temp|0x80);	 //暂
		ds1302_write(0x8e,0x80);		 //停
	}
	if(flag==2)
	{
		lcd1602_write_0(0xc0+4);
		lcd1602_write_0(0x0f);		  //光标到分位置
	}
	if(flag==3)
	{
		lcd1602_write_0(0xc0+1);
		lcd1602_write_0(0x0f);		   //光标到时位置
	}
	if(flag==4)
	{
		lcd1602_write_0(0x80+11);
		lcd1602_write_0(0x0f);			//光标到星期位置
	}
	if(flag==5)
	{
		lcd1602_write_0(0x80+9);
		lcd1602_write_0(0x0f);			//光标到日位置
	}
	if(flag==6)
	{
		lcd1602_write_0(0x80+6);
		lcd1602_write_0(0x0f);			//光标到月位置
	}
	if(flag==7)
	{
		lcd1602_write_0(0x80+3);
		lcd1602_write_0(0x0f);			//光标到年位置
	}
	if(flag>7)
	{
		ds1302_write(0x8e,0x00);	 	 //时
		temp=ds1302_read(0x81);		   	 //间
		ds1302_write(0x80,temp&0x7f);	 //启
		ds1302_write(0x8e,0x80);		 //动
		flag=0;
		lcd1602_write_0(0x0c);
	}		 
}

int main()
{ 	
	lcd1602_init();		 //LCD1602初始化
	lcd_zidingyi(zi,8,1);	  //自定义   C   写入
	lcd1602_X_Y(2,15,0x00);	  //   显示到  2行  15列
	stop();			  //中断初始化
	ds1302_init();		  //DS1302初始化
	while(1)
	{
		CE=1;				//板子问题  P35拉高

		read_temper(ds18b20_read_temp());	  //温度读取

		timer();				//时间读取
					
		lcd_display();		   //LCD显示

	  ctrltime();				//时间调整
	}  
}

void stop_1() interrupt 2
{
	delay_lcd(2000);
	if(k4==0)
	{
		flag++;
	}
}			   

void stop_2() interrupt 0
{
	uchar temp_1=0;
	delay_lcd(2000);
	if(k3==0)
	{
		if(flag>0&&flag<8)
		{		
			temp_1=ds1302_read(readdate_ctrl[flag-1]);
			temp_1++;
			if((temp_1&0x0f)>9)
			{
				temp_1=temp_1+6;
			}
			if(flag==1||flag==2)		   
			{
				if(temp_1==0x60)	   //秒和分最大60
				{
					temp_1=0x00;
				}
			}
			if(flag==3)
			{
				if(temp_1==0x24)	 //小时最大24
				{
					temp_1=0x00;
				}
			}
			if(flag==4)
			{
				if(temp_1==0x08)	//星期最大  7
				{
					temp_1=0x01;
				}
			}
			if(flag==5)
			{
				if(temp_1==0x32)	 //日  最大31
				{
					temp_1=0x01;
				}
			}
			if(flag==6)
			{
				if(temp_1==0x13)		//月最大12
				{
					temp_1=0x01;
				}
			}
			if(flag==7)
			{
				if(temp_1==0x31)	//以便 易调  年最大暂时设为  30
				{
					temp_1=0x01;
				}
			}
			ds1302_write(0x8e,0x00);
			ds1302_write(writedate_ctrl[flag-1],(temp_1));
			ds1302_write(0x8e,0x80);
		}
	}
}





/*
void time0() interrupt 1
{
	uint j;//i,g=10;
	TH0=thx;TL0=tlx;
	if(++j==100)
	{	
		j=0;
			
	}
}		 */




