#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

#define count 50000

#define TH_1 (65536-count)/256
#define TL_1 (65536-count)%256

bit write=0;		 //??????

sbit LA=P2^2;
sbit LB=P2^3;
sbit LC=P2^4;

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;

sbit scl=P2^1;
sbit sda=P2^0;

uchar duanxuan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};				//??  ?dp
uchar duanxuandp[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};			   //??   ?dp

uchar seconds=0,minute=0,iii=0,hour=0;
uchar month=1,dat=1;
uchar year=0,year_h=20;
uint switch1=0;		   //?????????

void yanshi(uint i)
{
	while(i--);
}


uint leapyear()
{
	 if((year%4==0&&year%100!=0)||(year%400==0))
	 	return 1;
	 else
	 	return 0;
}

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

/******************????************************/
void dateweixuan()		   //38  ???	 ????
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
		   
/******************????************************/
void timeweixuan()		   //38  ???	 ????
{
	uint i;
	for(i=0;i<6;i++)
	{
		switch(i)
		{
			case 0:LC=0;LB=0;LA=0;
			P0=duanxuan[seconds%10];break;				   	//????
			case 1:LC=0;LB=0;LA=1;
			P0=duanxuan[seconds/10];break;				  	 //????
			case 2:LC=0;LB=1;LA=0;
			P0=duanxuandp[minute%10];break;					 	//????
			case 3:LC=0;LB=1;LA=1;
			P0=duanxuan[minute/10];break;					        //????
			case 4:LC=1;LB=0;LA=0;
			P0=duanxuandp[hour%10];break;				 //?????
			case 5:LC=1;LB=0;LA=1;
			P0=duanxuan[hour/10];break;				   //?????
		}
		yanshi(100);
		P0=0x00;
	}
}

/********************???**************/
int main()
{	
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
	}
}

/****************?????*******************/
void time0() interrupt 1			   //?????  T0
{
	TL0=TL_1;TH0=TH_1;
	if(++iii==20)
	{
		iii=0;
		if(seconds<59)				   //???
			seconds++;
		else
		{
			seconds=0;
			if(minute<59)			  //????
				minute++;
			else
			{
				minute=0;
				if(hour<23)	
				{		   //????
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