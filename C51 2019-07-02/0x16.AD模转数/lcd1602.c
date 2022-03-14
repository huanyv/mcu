#include<lcd1602.h>

void delay_1(uint x)
{
	uint i,j;
	for(i=0;i<x;i++)
	for(j=0;j<10;j++);
}

void LCD_write_0(uchar dat)//д��ָ��
{
	LCD_DB=dat;
	LCD_RS=0;
	LCD_RW=0;
	LCD_E=1;
	LCD_E=0;
	delay_1(1);
}

void LCD_write_1(uchar dat)//��������  
{
	LCD_DB=dat;
	LCD_RS=1;
	LCD_RW=0;
	LCD_E=1;
	LCD_E=0;
	delay_1(1);
}
/*
void row(uint i)//�Զ�����ʾ��
{
	uint k;
	if(i==1)
	k=0x00;
	else
	k=0x40;
	LCD_write_0(0x80|k);
}							*/

void LCD_init()//��ʼ��
{
	LCD_write_0(0x38);
	delay_1(150);
	LCD_write_0(0x38);
	LCD_write_0(0x0c);
	LCD_write_0(0x06);
	LCD_write_0(0x01);
	delay_1(200);
	LCD_write_0(0x40);
}

 void LCD_X_Y(uchar x,uchar y,uchar date)//�Զ�����ʾ  λ��
 {
     uchar addr;
     if(x==1)
     {
         addr=0x80+y;
     }
     else
         addr=0xc0+y;
     LCD_write_0(addr);
     LCD_write_1(date);
 }
  /*
 void zidingyi(uchar *s,uint j)//�Զ�����ʾ  �ַ�
 {
 	uint i;
	for(i=0;i<j;i++)
    {
        LCD_write_1(s[i]);
    }
}  */