#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

#define count 50000

#define TH_1 (65536-count)/256
#define TL_1 (65536-count)%256

bit write=0;		 //写入控制变量

sbit LA=P2^2;
sbit LB=P2^3;
sbit LC=P2^4;

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;

sbit scl=P2^1;
sbit sda=P2^0;

uchar duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};				//段选  无dp
uchar duanxuandp[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};			   //段选   有dp

uchar seconds=0,minute=0,i=0,hour=0;
uchar month=1,dat=1;
uchar year=0,year_h=20;
uint switch1=0;		   //日期时间的判断变量

/*****************延时10us************/
void yanshi(uint i)
{
	while(i--);
}
/*****************延时5us************/
void delay5us()   //误差 0us
{
    unsigned char a;
    for(a=1;a>0;a--);
}

/***************开始信号*************/
void start()
{
	sda=1;
	delay5us();
	scl=1;
	delay5us();
	sda=0;
	delay5us();
	scl=0;
	delay5us();
}

/***************停止信号*************/
void stop()
{
	sda=0;
	delay5us();
	scl=1;
	delay5us();
	sda=1;
	delay5us();
}

/**************应答信号*************/
void respons()
{
	uchar i;
	scl=1;
	delay5us();
	while((sda==1)&&(i<255))
		i++;
	scl=0;
	delay5us();
}

/**************初始化*************/
void init()
{
	sda=1;
	delay5us();
	scl=1;
	delay5us();
}

/***************写一个字节**********/
void write_byte(uchar date)
{
	uchar i,t;
	t=date;
	for(i=0;i<8;i++)
	{
		t=t<<1;
		scl=0;
		delay5us();
		sda=CY;
		delay5us();
		scl=1;
		delay5us();
	}
	scl=0;
	delay5us();
	sda=1;
	delay5us();
}

/***************读一个字节************/
uchar read_byte()
{
	uchar i,k;
	scl=0;
	delay5us();
	sda=1;
   	delay5us();
	for(i=0;i<8;i++)
	{
		scl=1;
		delay5us();
		k=(k<<1)|sda;
		scl=0;
		delay5us();
	}
	return k;
}

/*****************写数据*******************/
void write_add(uchar addr,uchar date)
{
	start();
	write_byte(0xa0);
	respons();
	write_byte(addr);
	respons();
	write_byte(date);
	respons();
	stop();
}

/******************读数据*******************/
uchar read_addr(uchar addr)
{
	uchar date;
	start();
	write_byte(0xa0);
	respons();
	write_byte(addr);
	respons();
	start();
	write_byte(0xa1);
	respons();
	date=read_byte();
	stop();
	return date;
}

/************是否闰年************/
uint leapyear()
{
	 if((year%4==0&&year%100!=0)||(year%400==0))
	 	return 1;
	 else
	 	return 0;
}

/************判断天数************/
uint datnumber()
{
	if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
		return 31;
	else if(month==4||month==6||month==9||month==11)
		return 30;
	else 
	{
		if(leapyear()==1)
			return 29;
		else
			return 28;
	} 	
}

/**************日期控制***************/
void datekongzhi()
{
	static bit song=0;
	if(k3==0&&song==0)
	{
		yanshi(2000);
		if(k3==0)
		{
			song=1;
			dat++;
			if(dat==datnumber()+1)dat=1; 
		}
	}
	if(k2==0&&song==0)
	{
		yanshi(2000);
		if(k2==0)
		{
			song=1;
			month++;
			if(month==13)month=1; 
		}
	}
	if(k1==0&&song==0)
	{
		yanshi(2000);
		if(k1==0)
		{
			song=1;
			year++;
			if(year==100)
			{
				year=0;
				year_h++;
				if(year_h==100)
				year_h=20;
			} 
		}
	}
	if(k1==1&&k2==1&&k3==1){
		song=0;
	}
}
 /*************????***************/  
void timekongzhi()
{	
	static bit song=0;
	if(k3==0&&song==0)
	{
		yanshi(2000);
		if(k3==0)
		{
			song=1;
			seconds++;
			if(seconds==60)seconds=0; 
		}
	}
	if(k2==0&&song==0)
	{
		yanshi(2000);
		if(k2==0)
		{
			song=1;
			minute++;
			if(minute==60)minute=0; 
		}
	}
	if(k1==0&&song==0)
	{
		yanshi(2000);
		if(k1==0)
		{
			song=1;
			hour++;
			if(hour==24)hour=0; 
		}
	}
	if(k1==1&&k2==1&&k3==1){
		song=0;
	}
}
/******************日期位选************************/
void dateweixuan()		   //38  译码器	 日期位选
{
	uint i;
	for(i=0;i<8;i++)
	{
		switch(i)
		{
			case 0:LC=0;LB=0;LA=0;
			P0=duanxuan[dat%10];break;				   	
			case 1:LC=0;LB=0;LA=1;
			P0=duanxuan[dat/10];break;				  	 
			case 2:LC=0;LB=1;LA=0;
			P0=duanxuandp[month%10];break;				
			case 3:LC=0;LB=1;LA=1;
			P0=duanxuan[month/10];break;					    
			case 4:LC=1;LB=0;LA=0;
			P0=duanxuandp[year%10];break;			
			case 5:LC=1;LB=0;LA=1;
			P0=duanxuan[year/10];break;
			case 6:LC=1;LB=1;LA=0;
			P0=duanxuan[year_h%10];break;
			case 7:LC=1;LB=1;LA=1;
			P0=duanxuan[year_h/10];break;			
		}
		yanshi(100);
		P0=0x00;
	}
}
		   
/******************时间位选************************/
void timeweixuan()		   //38  译码器	 时间位选
{
	uint i;
	for(i=0;i<6;i++)
	{
		switch(i)
		{
			case 0:LC=0;LB=0;LA=0;
			P0=duanxuan[seconds%10];break;				   	//秒的个位
			case 1:LC=0;LB=0;LA=1;
			P0=duanxuan[seconds/10];break;				  	 //秒的十位
			case 2:LC=0;LB=1;LA=0;
			P0=duanxuandp[minute%10];break;					 	//分的个位
			case 3:LC=0;LB=1;LA=1;
			P0=duanxuan[minute/10];break;					        //分的十位
			case 4:LC=1;LB=0;LA=0;
			P0=duanxuandp[hour%10];break;				 //小时的个位
			case 5:LC=1;LB=0;LA=1;
			P0=duanxuan[hour/10];break;				   //小时的十位
		}
		yanshi(100);
		P0=0x00;
	}
}

/********************主函数**************/
int main()
{	
	init();
	seconds=read_addr(0x02);
	if(seconds>59)seconds=0;
	minute=read_addr(0x03);
	if(minute>100)minute=0;
	hour=read_addr(0x04);
	if(hour>23)hour=0;
	dat=read_addr(0x05);
	if(dat>31)dat=1;
	month=read_addr(0x06);
	if(month>13)month=1;
	year=read_addr(0x07);
	if(year>20)year=0;
	year_h=read_addr(0x08);
	if(year_h>99||year_h<20)year_h=20;	
	IE=0x82;
	TR0=1;
	TMOD=0x01;
	TL0=TL_1;TH0=TH_1;
	while(1)
	{
		if(switch1==0&&k4==0)
		{
			yanshi(2000);
			if(k4==0)
			{
				switch1=1;
				while(!k4);
			}
		}
		if(switch1==1&&k4==0)
		{
			yanshi(2000);
			if(k4==0)
			{
				switch1=0;
				while(!k4);
			}
		}
		if(switch1==0)
		{
			timekongzhi();
			timeweixuan();
		}
		if(switch1==1)
		{
			datekongzhi();
			dateweixuan();
		}
		if(write==1)
		{
			write=0;
			write_add(0x02,seconds); 
			yanshi(1000);  
			write_add(0x03,minute);
			yanshi(1000);
			write_add(0x04,hour);
			yanshi(1000);
			write_add(0x05,dat); 
			yanshi(1000);
			write_add(0x06,month);
			yanshi(1000);
			write_add(0x07,year);
			yanshi(1000);
			write_add(0x08,year_h);
			yanshi(1000);
		}
	}		
}

/****************定时器中断*******************/
void time0() interrupt 1			   //定时器中断  T0
{
	TL0=TL_1;TH0=TH_1;
	if(++i==20)
	{
		i=0;
		if(seconds<59)				   //秒变动
			seconds++;
		else
		{
			seconds=0;
			if(minute<59)			  //分钟进位
				minute++;
			else
			{
				minute=0;
				if(hour<23)	
				{		   //小时进位
					hour++;
					write=1;
				}
				else
				{
					hour=0;
					if(dat<datnumber())
						dat++;
					else
					{
						dat=1;
						if(month<12)
							month++;
						else
						{
							month=1;
							if(year<100)
							year++;
							else
							{
								year=0;
								year_h++;
							}
						}
					}
				}
			}
		}				
	}		
} 