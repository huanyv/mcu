#include "reg52.h"
#include "ds1302.h"
#include "key.h"

sbit LA=P2^2;
sbit LB=P2^3;
sbit LC=P2^4;

#define   dula   P0

uint time_dis[6];
uint date_dis[6];

uchar code tab[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};	

bit MENU1 = 0;

void delay(uint i) {
	while(i--);
}

void timer()
{
	read_time();

	time_dis[0]=time[3]/16; // 时
	time_dis[1]=time[3]%16;
	time_dis[2]=time[4]/16; // 分
	time_dis[3]=time[4]%16;
	time_dis[4]=time[5]/16; // 秒
	time_dis[5]=time[5]%16;

	date_dis[0]=time[0]/16; // 年
	date_dis[1]=time[0]%16;
	date_dis[2]=time[1]/16; // 月
	date_dis[3]=time[1]%16;
	date_dis[4]=time[2]/16; // 日
	date_dis[5]=time[2]%16;
}

void display()		   //38  译码器	 位选
{
	uint i;
	if(MENU1 == 0) {
		for(i=0;i<8;i++) {
				switch(i) {
						case 0:LC=0;LB=0;LA=0; dula= tab[time_dis[5]];break;				   	
						case 1:LC=0;LB=0;LA=1; dula= tab[time_dis[4]];break;				  	 
						case 2:LC=0;LB=1;LA=0; dula= 0x40;            break;		
						case 3:LC=0;LB=1;LA=1; dula= tab[time_dis[3]];break;					    
						case 4:LC=1;LB=0;LA=0; dula= tab[time_dis[2]];break;			
						case 5:LC=1;LB=0;LA=1; dula= 0x40;            break;
						case 6:LC=1;LB=1;LA=0; dula= tab[time_dis[1]];break;
						case 7:LC=1;LB=1;LA=1; dula= tab[time_dis[0]];break;			
				}
				delay(100);
				dula=0x00;
			}
	}
	else {
		for(i=0;i<8;i++) {
				switch(i) {
						case 0:LC=0;LB=0;LA=0; dula= tab[date_dis[5]];break;				   	
						case 1:LC=0;LB=0;LA=1; dula= tab[date_dis[4]];break;				  	 
						case 2:LC=0;LB=1;LA=0; dula= tab[date_dis[3]]|0x80;break;
						case 3:LC=0;LB=1;LA=1; dula= tab[date_dis[2]];break;					    
						case 4:LC=1;LB=0;LA=0; dula= tab[date_dis[1]]|0x80;break;			
						case 5:LC=1;LB=0;LA=1; dula= tab[date_dis[0]];break;
						case 6:LC=1;LB=1;LA=0; dula= tab[0];break;
						case 7:LC=1;LB=1;LA=1; dula= tab[2];break;
				}
			delay(100);
			dula=0x00;
		}
	}
}

sbit led = P2^0;

void KEY_crtl(void) {
	uchar KEY_VALUE = 0;
	uchar temp = 0; // 
  static bit TIME_STOP = 0;
	KEY_VALUE = read_key();
	if(KEY_VALUE == 4) {
		MENU1 = ~MENU1;
	}
	if(KEY_VALUE == 44) {

		TIME_STOP = ~TIME_STOP;
		if(TIME_STOP == 1) {
			ds1302_write(0x8e,0x00);		 //时
			temp=ds1302_read(0x81);			 //间
			ds1302_write(0x80,temp|0x80);	 //暂
			ds1302_write(0x8e,0x80);		 //停
		}
		if(TIME_STOP == 0) {
			ds1302_write(0x8e,0x00);		 //时
			temp=ds1302_read(0x81);			 //间
			ds1302_write(0x80,temp&0x7f);	 //启动
			ds1302_write(0x8e,0x80);	
		}
		
		led = ~led;
		
	}
	
	
	if((MENU1 == 0)&&(TIME_STOP == 1)) {
		if(KEY_VALUE == 3) {
			temp=(ds1302_read(0x81)|0x80);
			temp++;
			if((temp&0x0f)>9) {
				temp += 6;
			}
			if(temp == 0x60)
				temp = 0;
			ds1302_write(0x8e,0x00);
			ds1302_write(0x80,temp);
			ds1302_write(0x8e,0x80);
		}
		
		if(KEY_VALUE == 2) {
			temp=ds1302_read(0x83);
			temp++;
			if((temp&0x0f)>9) {
				temp += 6;
			}
			if(temp == 0x60)
				temp = 0;
			ds1302_write(0x8e,0x00);
			ds1302_write(0x82,temp);
			ds1302_write(0x8e,0x80);
		}
		
		if(KEY_VALUE == 1) {
			temp=ds1302_read(0x85);
			temp++;
			if((temp&0x0f)>9) {
				temp += 6;
			}
			if(temp == 0x24)
				temp = 0;
			ds1302_write(0x8e,0x00);
			ds1302_write(0x84,temp);
			ds1302_write(0x8e,0x80);
		}
	}
	
	if((MENU1 == 1)&&(TIME_STOP == 1)) {
		if(KEY_VALUE == 3) {
			temp=(ds1302_read(0x87)&0x7f);
			temp++;
			if((temp&0x0f)>9) {
				temp += 6;
			}
			if(temp == 0x32)
				temp = 1;
			ds1302_write(0x8e,0x00);
			ds1302_write(0x86,temp);
			ds1302_write(0x8e,0x80);
		}
		
		if(KEY_VALUE == 2) {
			temp=ds1302_read(0x89);
			temp++;
			if((temp&0x0f)>9) {
				temp += 6;
			}
			if(temp == 0x13)
				temp = 1;
			ds1302_write(0x8e,0x00);
			ds1302_write(0x88,temp);
			ds1302_write(0x8e,0x80);
		}
		
		if(KEY_VALUE == 1) {
			temp=ds1302_read(0x8D);
			temp++;
			if((temp&0x0f)>9) {
				temp += 6;
			}
			if(temp == 0x50)
				temp = 0;
			ds1302_write(0x8e,0x00);
			ds1302_write(0x8C,temp);
			ds1302_write(0x8e,0x80);
		}
	}
	
}

void main(void) {
	ds1302_init();
	while(1) {
		
		timer();
		display();
		KEY_crtl();
		


	}
}












