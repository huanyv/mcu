/***********************************************************************			   ||||||||||||||||||||
��ʼ����->����k4��������->ʱ����ͣ->k3����ʵʱʱ��->����ʾ����ʱ������			   |������Ϊ��bi~~~�� |
			   																		   |��δ���ģ���Щ�̶�|
��ʼ����->����k2�������ӽ���->k4����������->k3����ʱ��->k2���س�ʼ����			   ||||||||||||||||||||
			   
��ʼ����->����k1->ʵʱʱ������ʾС����ͼ��->����������->�ٴΰ�k1�ر�����			   
***********************************************************************/
#include<reg52.h>
#include<ds1302.h>
#include<ds18b20.h>			   //k4�����������              k3����ʱ��		       
#include<lcd1602.h>			   //k2������ʱ������л�		 k1���ӵ���ͣ
#include<intrins.h>

sbit k1=P3^1;//��
sbit k2=P3^0;//��
sbit k3=P3^2;//��
sbit k4=P3^3;//��

sbit beep=P1^5;//����������

uchar logo1[]=" MADE  BY ";
uchar logo2[]="Li yaolong";
uchar alarm[]="00:00";//����ʱ��
uchar temper[5];  //�¶�
uchar time_lcd[]="00:00:00";//ʵʱʱ��		  
uchar date_lcd[]="2000-00-00"; //ʵʱ����

uchar code readdate_ctrl[]={0x81,0x83,0x85,0x8b,0x87,0x89,0x8d};  //�������� 
uchar code writedate_ctrl[]={0x80,0x82,0x84,0x8a,0x86,0x88,0x8c}; //д������ 

uchar zi[3][8]={{0x10,0x06,0x09,0x08,0x08,0x09,0x06,0x00},	//���϶�ͼ��
				{0x0A,0x1F,0x15,0x17,0x11,0x0E,0x1B,0x00},	//����ͼ��
				{0x00,0x04,0x0E,0x1F,0x1F,0x1F,0x00,0x00}};	//ѡ��ͼ��

uchar week_lcd[][6]={{"error"},{"Mon."},{"Tues."},{"Wed."},{"Thur."},{"Fri."},{"Sat."},{"Sun."}};	//������ʾ����

#define count 50000
#define thx (65536-count)/256 //��ʱ�� ��ֵ  ��ʱδ��
#define tlx (65536-count)%256

uchar flag=0,flag1=0,flag2=0,flag3=0,ii=0;		  // flag:ʱ���꼰ʱ��������Ʊ���
											         //flag1:��Ļ�л�����
uint min=0,hour=0;										 //flag2:���ӹ�꼰ʱ���������
																//ii:������ͣ����
void delay6s()//����logoά��  6s  
{
    unsigned char a,b,c;
    for(c=182;c>0;c--)
        for(b=164;b>0;b--)
            for(a=99;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}
															

void logo()//����logo��ʾ 
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
	lcd1602_write_0(0x01);	   //��ʾ �� ����
	delay_lcd(2500);
}
							               
void read_temper(int dat)//�¶�ת������
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

void timer() //ʱ��ת������
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

void lcd_display()//LCD1602��ʾ����
{ 
	uint i,j,k=0,g=10;
	if(flag1==0)
	{	
//******************************************* 
		for(i=0;date_lcd[i]!='\0';i++)
		{				  
			lcd1602_X_Y(1,j++,date_lcd[i]);//������ʾ 
		}j++;
//*******************************************
		for(i=0;week_lcd[6][i]!='\0';i++)
		{
			lcd1602_X_Y(1,j++,week_lcd[time[6]][i]);//������ʾ 
		}
//*******************************************		 
		for(i=0;time_lcd[i]!='\0';i++)
		{
			lcd1602_X_Y(2,k++,time_lcd[i]);	//ʱ����ʾ
		}
//*******************************************		
		for(i=0;i<5;i++)
		{
			lcd1602_X_Y(2,g++,temper[i]);	//�¶���ʾ
		}
	}
		
//*******************************************
	if(flag==0&&flag1==1)			  //��һ�ΰ���k2���� 
	{
		lcd1602_write_0(0x01);
		delay_lcd(2500);
		lcd1602_write_0(0x01);
		flag1=2;
	}

	if(flag==0&&flag1==2)  //���ӽ�����ʾ
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
	if(flag==0&&flag1==3)		  //�ڶ��� ����k2����
	{
		lcd1602_write_0(0x01);
		delay_lcd(2500);
		lcd1602_write_0(0x01);
		flag1=4;
	}
	if(flag==0&&flag1==4)	  //�ص�  ��ʼ  ʱ��  ����
	{
		flag1=0;
		lcd_zidingyi(zi,8,1);	  
		lcd1602_X_Y(2,15,0x00);
	}
	alarm[4]=min%10+'0';	 //��
	alarm[3]=min/10+'0';	 //��
	alarm[1]=hour%10+'0';	 //ʱ
	alarm[0]=hour/10+'0';	 //��

	if(flag3==1&&flag1!=2)	   //��������   ʱ���� ��ʾ����Сͼ�� 
	{
		lcd1602_write_0(0x48);
		for(i=0;i<8;i++)
		{
			 lcd1602_write_1(zi[1][i]);
		}
		lcd1602_write_0(0xc0+8);
		lcd1602_write_1(0x01);
	}
	if(flag3==2)			 //�ر�����   ʱ���� ����ʾ����Сͼ��
	{
		lcd1602_write_0(0xc0+8);
		lcd1602_write_1(' ');
	}
	if(flag3==3)	  //ѭ������
	{
		flag3=1;
	}
}

void stop()//�ⲿ�ж�0��1 ��ʼ��
{
	EA=1;EX0=1;IT0=1;
	EX1=1;IT1=1;
}

void ctrltime()//�����ƺ���
{
	uchar temp;
	uint i;
	if(flag1==0)
	{
		if(flag==1)
		{
			lcd1602_write_0(0xc0+7);
			lcd1602_write_0(0x0f);			//��굽��λ��
	
			ds1302_write(0x8e,0x00);		 //ʱ
			temp=ds1302_read(0x81);			 //��
			ds1302_write(0x80,temp|0x80);	 //��
			ds1302_write(0x8e,0x80);		 //ͣ
		}
		if(flag==2)
		{
			lcd1602_write_0(0xc0+4);
			lcd1602_write_0(0x0f);		  //��굽��λ��
		}
		if(flag==3)
		{
			lcd1602_write_0(0xc0+1);
			lcd1602_write_0(0x0f);		   //��굽ʱλ��
		}
		if(flag==4)
		{
			lcd1602_write_0(0x80+11);
			lcd1602_write_0(0x0f);			//��굽����λ��
		}
		if(flag==5)
		{
			lcd1602_write_0(0x80+9);
			lcd1602_write_0(0x0f);			//��굽��λ��
		}
		if(flag==6)
		{
			lcd1602_write_0(0x80+6);
			lcd1602_write_0(0x0f);			//��굽��λ��
		}
		if(flag==7)
		{
			lcd1602_write_0(0x80+3);
			lcd1602_write_0(0x0f);			//��굽��λ��
		}
		if(flag>7)
		{
			ds1302_write(0x8e,0x00);	 	 //ʱ
			temp=ds1302_read(0x81);		   	 //��
			ds1302_write(0x80,temp|0x00);	 //��
			ds1302_write(0x8e,0x80);		 //��
			flag=0;
			lcd1602_write_0(0x0c);
		}
	}
	if(flag==0&&flag1==2&&flag2!=0)
	{
		switch(flag2)
		{
			case 1:			  //���  ����  ��  ��������   ����  λ
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
			case 2:			   //���  ����  ��  ��������   Сʱ  λ
				lcd1602_write_0(0xc0+9);		 
				lcd1602_write_1(' ');
				lcd1602_write_0(0xc0+10);		 
				lcd1602_write_1(' ');	
				lcd1602_write_0(0xc0+6);		 
				lcd1602_write_1(0x02);
				lcd1602_write_0(0xc0+7);		 
				lcd1602_write_1(0x02);	 break;
			case 3:				//���  ѭ��  ����
				flag2=1;                 break;
		}		
	}			 
}

void key_2()//k2����  ���� ���ý���
{
	if(k2==0)
	{
		delay_lcd(2000);
		if(k2==0)
		{
			if(flag==0)		  //���û����  ����ʱ��  ���� 	��Ļ�л�����
			{
				flag1++;
			}
		}
		while(k2==0);		 
	}	
}




void key_1()//k1���ӵ���ͣ
{
	if(k1==0)
	{
		delay_lcd(2000);
		if(k1==0)
		{
			if(flag==0&&flag1==0)			//����ڳ�ʼ���沢��û����
			{								//�������ý���   ����������ͣ����
				flag3++;
			}
			
		}
		while(k1==0);
	}
}


void buling()	  //���Ӵ���
{
	uint t1,t2,temp_min,temp_hour,i;
	if(flag3==1&&ii==0&&flag==0)
	{
		t1=ds1302_read(0x83);t2=ds1302_read(0x85);
	  	temp_min =((t1&0xf0)>>4)*10+(t1&0x0f);	//BCD��ת
		temp_hour=((t2&0xf0)>>4)*10+(t2&0x0f);			//ʮ������
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
						beep=~beep;					  //������
						delay_lcd(10);
						if(k1==0)
						{
							delay_lcd(2000);
							if(k1==0)		 //k1����  ����  ֹͣ
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

int main()//������ 
{ 	
	lcd1602_init();		 //LCD1602��ʼ��
	logo();
	lcd_zidingyi(zi,8,1);	  //�Զ���   C   д��
	lcd1602_X_Y(2,15,0x00);	  //   ��ʾ��  2��  15��
	stop();			  //�жϳ�ʼ��
	ds1302_init();		  //DS1302��ʼ��
	while(1)
	{
		CE=1;				//��������  P35����

		read_temper(ds18b20_read_temp());	  //�¶ȶ�ȡ

		timer();//ʱ���ȡ

		key_2(); //k2����  ���� ���ý���

		key_1();//k1���ӵ���ͣ

		buling(); //���Ӵ���
			
		lcd_display();		   //LCD��ʾ

	  	ctrltime();				//ʱ�����
	}  
	return 0;
}

void stop_1() interrupt 2//�ⲿ �ж� 1	 ������
{
	delay_lcd(2000);
	if(k4==0)
	{
		if(flag1==0)	//���û�����������ý���   ʱ�������� ����  
		{
			flag++;
		}
		if(flag1==2)	//������������ý���   ���ӵ������	���� 
		{
			flag2++;
		}
	}
	while(k4==0);
}			   

void stop_2() interrupt 0//�ⲿ �ж� 0	   ʱ�����
{
	uchar temp_1=0;
	delay_lcd(2000);
	if(k3==0)
	{
		if((flag>0&&flag<8)&&flag1==0)	  //��� �� ���  ��  û���������ý��� ����ʱ�����
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
				if(temp_1==0x60)	   //��ͷ����59
				{
					temp_1=0x00;
				}
			}
			if(flag==3)
			{
				if(temp_1==0x24)	 //Сʱ���23
				{
					temp_1=0x00;
				}
			}
			if(flag==4)
			{
				if(temp_1==0x08)	//�������  7
				{
					temp_1=0x01;
				}
			}
			if(flag==5)
			{
				if(temp_1==0x32)	 //��  ���31
				{
					temp_1=0x01;
				}
			}
			if(flag==6)
			{
				if(temp_1==0x13)		//�����12
				{
					temp_1=0x01;
				}
			}
			if(flag==7)
			{
				if(temp_1==0x31)	//�Ա� ����  �������ʱ��Ϊ  30
				{
					temp_1=0x00;
				}
			}
			ds1302_write(writedate_ctrl[flag-1],temp_1);
			ds1302_write(0x8e,0x80);
		
		} 
		if(flag==0&&flag1==2&&flag2==1)				//���ӽ�����ӵ���
		{
			min++;
			if(min==60)min=0;	
		}
		if(flag==0&&flag1==2&&flag2==2)				//���ӽ���Сʱ����
		{
			hour++;
			if(hour==24)hour=0;	
		}
		while(k3==0);
	}
	
}






















