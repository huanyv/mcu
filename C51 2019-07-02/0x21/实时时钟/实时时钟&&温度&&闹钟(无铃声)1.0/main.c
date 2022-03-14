/***********************************************************************			   ||||||||||||||||||||
初始界面->按下k4进入设置->时间暂停->k3调整实时时间->不显示光标后时间启动			   |铃声暂为长bi~~~声 |
			   																		   |还未更改，有些刺耳|
初始界面->按下k2进入闹钟界面->k4设置响铃光标->k3调整时间->k2返回初始界面			   ||||||||||||||||||||
			   
初始界面->按下k1->实时时间旁显示小闹钟图标->闹钟已启动->再次按k1关闭闹钟			   
***********************************************************************/
#include<reg52.h>
#include<ds1302.h>
#include<ds18b20.h>			   //k4进入调整设置              k3调整时间		       
#include<lcd1602.h>			   //k2闹钟与时间界面切换		 k1闹钟的启停
#include<intrins.h>

sbit k1=P3^1;//开
sbit k2=P3^0;//关
sbit k3=P3^2;//定
sbit k4=P3^3;//义

sbit beep=P1^5;//蜂鸣器定义

uchar logo1[]=" MADE  BY ";
uchar logo2[]="Li yaolong";
uchar alarm[]="00:00";//闹钟时间
uchar temper[5];  //温度
uchar time_lcd[]="00:00:00";//实时时间		  
uchar date_lcd[]="2000-00-00"; //实时日期

uchar code readdate_ctrl[]={0x81,0x83,0x85,0x8b,0x87,0x89,0x8d};  //读用数组 
uchar code writedate_ctrl[]={0x80,0x82,0x84,0x8a,0x86,0x88,0x8c}; //写用数组 

uchar zi[3][8]={{0x10,0x06,0x09,0x08,0x08,0x09,0x06,0x00},	//摄氏度图标
				{0x0A,0x1F,0x15,0x17,0x11,0x0E,0x1B,0x00},	//闹钟图标
				{0x00,0x04,0x0E,0x1F,0x1F,0x1F,0x00,0x00}};	//选中图标

uchar week_lcd[][6]={{"error"},{"Mon."},{"Tues."},{"Wed."},{"Thur."},{"Fri."},{"Sat."},{"Sun."}};	//星期显示数组

#define count 50000
#define thx (65536-count)/256 //定时器 初值  暂时未用
#define tlx (65536-count)%256

uchar flag=0,flag1=0,flag2=0,flag3=0,ii=0;		  // flag:时间光标及时间调整控制变量
											         //flag1:屏幕切换变量
uint min=0,hour=0;										 //flag2:闹钟光标及时间调整变量
																//ii:闹钟启停变量
void delay6s()//开机logo维持  6s  
{
    unsigned char a,b,c;
    for(c=182;c>0;c--)
        for(b=164;b>0;b--)
            for(a=99;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}
															

void logo()//开机logo显示 
{
	uint k1,k2=3;
	for(k1=0;logo1[k1]!='\0';k1++)
	{
		lcd1602_X_Y(1,k2++,logo1[k1]);
	} 
	k2=3;
	for(k1=0;logo2[k1]!='\0';k1++)
	{
		lcd1602_X_Y(2,k2++,logo2[k1]);
	}delay6s();
	lcd1602_write_0(0x01);	   //显示 完 清屏
	delay_lcd(2500);
}
							               
void read_temper(int dat)//温度转换函数
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

void timer() //时间转换函数
{
	read_time();

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

void lcd_display()//LCD1602显示函数
{ 
	uint i,j,k=0,g=10;
	if(flag1==0)
	{	
//******************************************* 
		for(i=0;date_lcd[i]!='\0';i++)
		{				  
			lcd1602_X_Y(1,j++,date_lcd[i]);//日期显示 
		}j++;
//*******************************************
		for(i=0;week_lcd[6][i]!='\0';i++)
		{
			lcd1602_X_Y(1,j++,week_lcd[time[6]][i]);//星期显示 
		}
//*******************************************		 
		for(i=0;time_lcd[i]!='\0';i++)
		{
			lcd1602_X_Y(2,k++,time_lcd[i]);	//时间显示
		}
//*******************************************		
		for(i=0;i<5;i++)
		{
			lcd1602_X_Y(2,g++,temper[i]);	//温度显示
		}
	}
		
//*******************************************
	if(flag==0&&flag1==1)			  //第一次按下k2清屏 
	{
		lcd1602_write_0(0x01);
		delay_lcd(2500);
		lcd1602_write_0(0x01);
		flag1=2;
	}

	if(flag==0&&flag1==2)  //闹钟界面显示
	{
		lcd1602_write_0(0x48);
		for(i=0;i<8;i++)
		{
			 lcd1602_write_1(zi[1][i]);
		}	
		lcd1602_write_0(0x80+5);		 
		lcd1602_write_1(0x01);
		lcd1602_write_0(0x80+6);
		lcd1602_write_1(alarm[0]);
		lcd1602_write_0(0x80+7);
		lcd1602_write_1(alarm[1]);
		lcd1602_write_0(0x80+8);
		lcd1602_write_1(alarm[2]);
		lcd1602_write_0(0x80+9);
		lcd1602_write_1(alarm[3]);
		lcd1602_write_0(0x80+10);	
		lcd1602_write_1(alarm[4]);
		lcd1602_write_0(0x80);
		lcd1602_write_1(' ');
	}
	if(flag==0&&flag1==3)		  //第二次 按下k2清屏
	{
		lcd1602_write_0(0x01);
		delay_lcd(2500);
		lcd1602_write_0(0x01);
		flag1=4;
	}
	if(flag==0&&flag1==4)	  //回到  初始  时间  界面
	{
		flag1=0;
		lcd_zidingyi(zi,8,1);	  
		lcd1602_X_Y(2,15,0x00);
	}
	alarm[4]=min%10+'0';	 //闹
	alarm[3]=min/10+'0';	 //钟
	alarm[1]=hour%10+'0';	 //时
	alarm[0]=hour/10+'0';	 //间

	if(flag3==1&&flag1!=2)	   //开启闹钟   时间旁 显示闹钟小图标 
	{
		lcd1602_write_0(0x48);
		for(i=0;i<8;i++)
		{
			 lcd1602_write_1(zi[1][i]);
		}
		lcd1602_write_0(0xc0+8);
		lcd1602_write_1(0x01);
	}
	if(flag3==2)			 //关闭闹钟   时间旁 不显示闹钟小图标
	{
		lcd1602_write_0(0xc0+8);
		lcd1602_write_1(' ');
	}
	if(flag3==3)	  //循环返回
	{
		flag3=1;
	}
}

void stop()//外部中断0和1 初始化
{
	EA=1;EX0=1;IT0=1;
	EX1=1;IT1=1;
}

void ctrltime()//光标控制函数
{
	uchar temp;
	uint i;
	if(flag1==0)
	{
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
			ds1302_write(0x80,temp|0x00);	 //启
			ds1302_write(0x8e,0x80);		 //动
			flag=0;
			lcd1602_write_0(0x0c);
		}
	}
	if(flag==0&&flag1==2&&flag2!=0)
	{
		switch(flag2)
		{
			case 1:			  //光标  定格  在  闹钟设置   分钟  位
				lcd1602_write_0(0x50);
				for(i=0;i<8;i++)
				{
					 lcd1602_write_1(zi[2][i]);
				}
				lcd1602_write_0(0xc0+6);		 
				lcd1602_write_1(' ');
				lcd1602_write_0(0xc0+7);		 
				lcd1602_write_1(' ');	
				lcd1602_write_0(0xc0+9);		 
				lcd1602_write_1(0x02);
				lcd1602_write_0(0xc0+10);		 
				lcd1602_write_1(0x02);	 break;
			case 2:			   //光标  定格  在  闹钟设置   小时  位
				lcd1602_write_0(0xc0+9);		 
				lcd1602_write_1(' ');
				lcd1602_write_0(0xc0+10);		 
				lcd1602_write_1(' ');	
				lcd1602_write_0(0xc0+6);		 
				lcd1602_write_1(0x02);
				lcd1602_write_0(0xc0+7);		 
				lcd1602_write_1(0x02);	 break;
			case 3:				//光标  循环  返回
				flag2=1;                 break;
		}		
	}			 
}

void key_2()//k2更换  闹钟 设置界面
{
	if(k2==0)
	{
		delay_lcd(2000);
		if(k2==0)
		{
			if(flag==0)		  //如果没有在  调整时间  触发 	屏幕切换变量
			{
				flag1++;
			}
		}
		while(k2==0);		 
	}	
}




void key_1()//k1闹钟的启停
{
	if(k1==0)
	{
		delay_lcd(2000);
		if(k1==0)
		{
			if(flag==0&&flag1==0)			//如果在初始界面并且没有在
			{								//闹钟设置界面   触发闹钟启停变量
				flag3++;
			}
			
		}
		while(k1==0);
	}
}


void buling()	  //闹钟触发
{
	uint t1,t2,temp_min,temp_hour,i;
	if(flag3==1&&ii==0&&flag==0)
	{
		t1=ds1302_read(0x83);t2=ds1302_read(0x85);
	  	temp_min =((t1&0xf0)>>4)*10+(t1&0x0f);	//BCD码转
		temp_hour=((t2&0xf0)>>4)*10+(t2&0x0f);			//十进制码
		if(min==temp_min&&ii==0)				
		{
			if(hour==temp_hour&&ii==0)
			{
				if(flag==0&&ii==0)
				{
					lcd1602_write_0(0x01);
					delay_lcd(2500);
					lcd1602_write_0(0x48);
					for(i=0;i<8;i++)
					{
						 lcd1602_write_1(zi[1][i]);
					}							 
					lcd1602_write_0(0x80+5);		 
					lcd1602_write_1(0x01);
					lcd1602_write_0(0x80+6);
					lcd1602_write_1(alarm[0]);
					lcd1602_write_0(0x80+7);
					lcd1602_write_1(alarm[1]);
					lcd1602_write_0(0x80+8);
					lcd1602_write_1(alarm[2]);
					lcd1602_write_0(0x80+9);
					lcd1602_write_1(alarm[3]);
					lcd1602_write_0(0x80+10);	
					lcd1602_write_1(alarm[4]);
					lcd1602_write_0(0x80);
					lcd1602_write_1(' ');
					while(ii==0)
					{
						beep=~beep;					  //闹钟响
						delay_lcd(10);
						if(k1==0)
						{
							delay_lcd(2000);
							if(k1==0)		 //k1按下  闹钟  停止
							{	
								flag1=3;
								flag3=2;
								ii=1;	
							}
							while(k1==0);
						}
					}
					ii=0;
					lcd_zidingyi(zi,8,1);	  
					lcd1602_X_Y(2,15,0x00);
				}
			}
		} 
	}
}

int main()//主函数 
{ 	
	lcd1602_init();		 //LCD1602初始化
	logo();
	lcd_zidingyi(zi,8,1);	  //自定义   C   写入
	lcd1602_X_Y(2,15,0x00);	  //   显示到  2行  15列
	stop();			  //中断初始化
	ds1302_init();		  //DS1302初始化
	while(1)
	{
		CE=1;				//板子问题  P35拉高

		read_temper(ds18b20_read_temp());	  //温度读取

		timer();//时间读取

		key_2(); //k2更换  闹钟 设置界面

		key_1();//k1闹钟的启停

		buling(); //闹钟触发
			
		lcd_display();		   //LCD显示

	  	ctrltime();				//时间调整
	}  
	return 0;
}

void stop_1() interrupt 2//外部 中断 1	 光标控制
{
	delay_lcd(2000);
	if(k4==0)
	{
		if(flag1==0)	//如果没有在闹钟设置界面   时间调整光标 控制  
		{
			flag++;
		}
		if(flag1==2)	//如果在闹钟设置界面   闹钟调整光标	控制 
		{
			flag2++;
		}
	}
	while(k4==0);
}			   

void stop_2() interrupt 0//外部 中断 0	   时间更改
{
	uchar temp_1=0;
	delay_lcd(2000);
	if(k3==0)
	{
		if((flag>0&&flag<8)&&flag1==0)	  //如果 有 光标  且  没在闹钟设置界面 触发时间调整
		{		
			ds1302_write(0x8e,0x00);
			temp_1=ds1302_read(readdate_ctrl[flag-1]);
			temp_1++;
			if((temp_1&0x0f)>9)
			{
				temp_1=temp_1+6;
			}	 
			if(flag==1||flag==2)		   
			{
				if(temp_1==0x60)	   //秒和分最大59
				{
					temp_1=0x00;
				}
			}
			if(flag==3)
			{
				if(temp_1==0x24)	 //小时最大23
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
				if(temp_1==0x31)	//以便 调整  年最大暂时设为  30
				{
					temp_1=0x00;
				}
			}
			ds1302_write(writedate_ctrl[flag-1],temp_1);
			ds1302_write(0x8e,0x80);
		
		} 
		if(flag==0&&flag1==2&&flag2==1)				//闹钟界面分钟调整
		{
			min++;
			if(min==60)min=0;	
		}
		if(flag==0&&flag1==2&&flag2==2)				//闹钟界面小时调整
		{
			hour++;
			if(hour==24)hour=0;	
		}
		while(k3==0);
	}
	
}






















