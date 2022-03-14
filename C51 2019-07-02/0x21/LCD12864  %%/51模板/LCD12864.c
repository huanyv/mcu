#include"reg52.h"
#include"lcd12864.h"
#include"intrins.h"
void delay(unsigned int i) {//延时
	while(i--);
}
unsigned char LCD_Read_Busy() {//读忙
	unsigned char Busy_count = 0;
	LCD_RS = 0;
	LCD_RW = 1;
	LCD_EN = 1;
	_nop_();
	Busy_count = (LCD_DATA&0X80)>>8;
	if(Busy_count == 0x01) {
		Busy_count = 1;
	}
	else {
		Busy_count = 0;
	}
	LCD_EN = 0;
	return Busy_count;
}
void LCD_WriteData(unsigned char dat) {//写指令
	while(LCD_Read_Busy == 1);
	LCD_RS = 1;
	LCD_RW = 0;
	_nop_();
	LCD_EN = 1;
	LCD_DATA = dat;
	_nop_();
	LCD_EN = 0;
	_nop_();
}
void LCD_WriteCmd(unsigned char dat) {//写数据 
	while(LCD_Read_Busy == 1);
	LCD_RS = 0;
	LCD_RW = 0;
	_nop_();
	LCD_EN = 1;
	LCD_DATA = dat;
	_nop_();
	LCD_EN = 0;
	_nop_();
}
void LCD_Pos(unsigned char X,unsigned char Y)
{                          
   unsigned char pos;
   if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}
   pos = X+Y ;  
   LCD_WriteCmd(pos);     //????
}
void LCD_Init()
{

    LCD_PSB = 1;       
   
    LCD_WriteCmd(0x34);      
    delay(5);
    LCD_WriteCmd(0x30);    
    delay(5);
    LCD_WriteCmd(0x0C);     
    delay(5);
    LCD_WriteCmd(0x01);      
    delay(5);
}






