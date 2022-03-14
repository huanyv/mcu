#include<reg52.h>
#include "ds18b20.h"
#include "lcd1602.h"

sbit LA=P2^2;
sbit LB=P2^3;
sbit LC=P2^4;

#define count 50000
#define THx (65536-count)/256
#define TLx (65536-count)%256

uchar lcd1602[8],flag_1,flag_2,sec=0;
uchar temperature[]="Temperature:";			   //LCD����

uchar CRC[8];

void datapros()
{
    int temp = 0;
    float tp;

		temp = readc();

    if(temp< 0)
    {
        lcd1602[0]='-';
        temp=temp-1;
        temp=~temp;
        tp=temp;
        temp=tp*0.0625*100+0.5;
    }
    else
    {
        lcd1602[0]='+';
        tp=temp;
        temp=tp*0.0625*100+0.5;
    }
    lcd1602[1]=temp/10000+48;
    lcd1602[2]=temp/1000%10+48;
    lcd1602[3]=temp/100%10+48;
    lcd1602[4]='.';
    lcd1602[5]=temp/10%10+48;
    lcd1602[6]=temp%10+48;
}

void time0init()
{
    TMOD=0x01;
    TH0=THx;
    TL0=TLx;
    EA=1;
    ET0=1;
    TR0=1;
}



void Read_ROM(void) {
	uint i;
	uchar code chartab[] = "0123456789ABCDEF";
	for(i = 0;i<8; i++) {
			CRC[i]=0;
		}
		DS18B20_init();
		DS18B20_write(0x33);
		for(i = 0;i<8; i++) {
			CRC[i]=DS18B20_read();
		}
		LCD_write_0(0x80);
		LCD_write_1(chartab[CRC[0]/16]);
		LCD_write_1(chartab[CRC[0]%16]);
		LCD_write_1(chartab[CRC[1]/16]);
		LCD_write_1(chartab[CRC[1]%16]);
		LCD_write_1(chartab[CRC[2]/16]);
		LCD_write_1(chartab[CRC[2]%16]);
		LCD_write_1(chartab[CRC[3]/16]);
		LCD_write_1(chartab[CRC[3]%16]);
		LCD_write_1(chartab[CRC[4]/16]);
		LCD_write_1(chartab[CRC[4]%16]);
		LCD_write_1(chartab[CRC[5]/16]);
		LCD_write_1(chartab[CRC[5]%16]);
		LCD_write_1(chartab[CRC[6]/16]);
		LCD_write_1(chartab[CRC[6]%16]);
		LCD_write_1(chartab[CRC[7]/16]);
		LCD_write_1(chartab[CRC[7]%16]);
}

int main()
{
    uint i,j,k=0;
    uchar table1[]= {0x10,0x06,0x09,0x08,0x08,0x09,0x06,0x00};  			//�Զ����¶ȷ���
    time0init(); // ��ʼ����ʱ��
    LCD_init(); // ��ʼ��LCD
    zidingyi(table1,8); // �����Զ��ַ�
    LCD_X_Y(2,11,0x00); // ��ʾ ��һ���ַ���  2��11��
		
		Read_ROM(); // �����ROM
    while(1)
    {
        j=4;
        if(flag_2==1)
        {
            datapros();
            flag_2=0;
        }
				
				
        for(i=0; lcd1602[i]!='\0'; i++)
        {
            LCD_X_Y(2,j++,lcd1602[i]);				 //
            delay(100);
            if(j==12)j=4;
        }
    }
}
void time0() interrupt 1
{
    if(++flag_1==20)
    {
        flag_1=0;
        flag_2=1;
        sec++;
        if(sec==60)sec=0;
    }
}