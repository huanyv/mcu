#include "oled_display.h"
#include "ds1302.h"
#include "oled_i2c.h"
#include "18b20.h"
#include "key.h"

uint8_t time_lcd[]="00:00:00";
uint8_t date_lcd[]="2000-00-00";

uint8_t week_lcd[][6]={{"error"},{"Mon."},{"Tues."},{"Wed."},{"Thur."},{"Fri."},{"Sat."},{"Sun."}};

uint8_t Temperature[] = " 25.00C";

void Temp_Conversion(void) {
	int temp;
	float tt;
	CE = 1; // �������� ���� PA13 �ɴ��� 18B20�����ݿ�
	temp = Read_Temp();
	if(temp<0) {
		Temperature[0] = '-';
		temp = temp - 1;
		temp = ~temp;
		tt = temp;
		temp = tt * 0.0625 * 100 + 0.5;
	}
	else {
		Temperature[0] = ' ';
		tt = temp;
		temp = tt * 0.0625 * 100 + 0.5;
	}
	Temperature[1] = temp/1000%10+48; // �¶�ת��
	Temperature[2] = temp/100%10+48;
	Temperature[3] = '.';
	Temperature[4] = temp/10%10+48;
	Temperature[5] = temp%10+48;
	Temperature[6] = 95+32;
}


void display(void) {
	DS1302_ReadTime();//ʱ��ת��

	time_lcd[0]=time[3]/16+'0';
	if(time_lcd[0] == '0')
		time_lcd[0] = ' ';   // ʱ �� ��0��
	time_lcd[1]=time[3]%16+'0';
	time_lcd[2]=':';
	time_lcd[3]=time[4]/16+'0';
	time_lcd[4]=time[4]%16+'0';
	time_lcd[5]=':';
	time_lcd[6]=time[5]/16+'0';
	time_lcd[7]=time[5]%16+'0';
	
	date_lcd[0]='2';
	date_lcd[1]='0';
	date_lcd[2]=time[0]/16+'0';
	date_lcd[3]=time[0]%16+'0';
	date_lcd[4]='-';
	date_lcd[5]=time[1]/16+'0';
	date_lcd[6]=time[1]%16+'0';
	date_lcd[7]='-';
	date_lcd[8]=time[2]/16+'0';
	date_lcd[9]=time[2]%16+'0';
	
	OLED_Show16x32(0,2,time_lcd);//ʱ����ʾ 
	OLED_ShowStr(0,0,date_lcd,2);//������ʾ 
	OLED_ShowStr(88,0,week_lcd[time[6]],2);//������ʾ 
	
	
	Temp_Conversion(); // ��ȡ�¶�
	
	OLED_ShowStr(0,6,Temperature,2);//�¶���ʾ 
	
}

void KEY_Crtl_display(void) {
	uint8_t temp;

	if(MENU1 == 1) {
		Write_DS1302(0x8e,0x00);		   //ʱ
		temp=Read_DS1302(0x81);			   //��
		Write_DS1302(0x80,temp|0x80);  //��
		Write_DS1302(0x8e,0x80);       //ͣ
		
		OLED_Show16x32(96,2,"  ");//������
	
	}
	if(MENU1 == 2) {
		
		OLED_Show16x32(48,2,"  ");//������
	
	}
	if(MENU1 == 3) {
		
		OLED_Show16x32(0,2,"  ");//ʱ����
	
	}	
	if(MENU1 == 4) {
		
		OLED_ShowStr(88,0,"     ",2);//��������
	
	}	
	if(MENU1 == 5) {
		
		OLED_ShowStr(64,0,"  ",2);//������
	
	}
	if(MENU1 == 6) {
		
		OLED_ShowStr(40,0,"  ",2);//������
	
	}
	if(MENU1 == 7) {
		
		OLED_ShowStr(0,0,"    ",2);//������
	
	}
	if(MENU1 == 8) {
		
		Write_DS1302(0x8e,0x00);		   //ʱ
		temp=Read_DS1302(0x81);			   //��
		Write_DS1302(0x80,temp&0x7F);  //��
		Write_DS1302(0x8e,0x80);       //��
		MENU1 = 0;
	}
}


