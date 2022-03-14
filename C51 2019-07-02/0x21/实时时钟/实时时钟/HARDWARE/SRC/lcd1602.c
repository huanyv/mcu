#include<lcd1602.h>
#include<intrins.h>

void delay_lcd(uint iii)
{
	while(iii--);
}

void lcd1602_write_0(uchar dat)
{
	LCD_DB=dat;
	LCD_RS=0;
	LCD_RW=0;
	LCD_EN=1;
	LCD_EN=0;
	delay_lcd(10);
}

void lcd1602_write_1(uchar dat)
{
	LCD_DB=dat;
	LCD_RS=1;
	LCD_RW=0;
	LCD_EN=1;
	LCD_EN=0;
	delay_lcd(10);
}

void lcd_zidingyi(uchar (*s)[],uchar i_1,uchar i_2)
{
	uchar j_1,j_2;
	for(j_1=1;j_1<=i_2;j_1++)
	{
		if(j_1==1)
			lcd1602_write_0(0x40);
		if(j_1==2)
			lcd1602_write_0(0x48);
		if(j_1==3)
			lcd1602_write_0(0x50);
		if(j_1==4)
			lcd1602_write_0(0x58);
		if(j_1==5)
			lcd1602_write_0(0x60);
		if(j_1==6)
			lcd1602_write_0(0x68);
		if(j_1==7)
			lcd1602_write_0(0x70);
		if(j_1==8)
			lcd1602_write_0(0x78);
			for(j_2=0;j_2<i_1;j_2++)
			{
				 lcd1602_write_1(s[j_1-1][j_2]);
			}
	}
}

void lcd1602_X_Y(uchar x,uchar y,uchar dat)
{
	uchar add;
	if(x==1)
	{
		add=0x80+y;
	}
	else
		add=0xc0+y;
	lcd1602_write_0(add);
    lcd1602_write_1(dat);
}

void lcd1602_init()
{
	lcd1602_write_0(0x38);
	delay_lcd(1500);
	lcd1602_write_0(0x38);
	lcd1602_write_0(0x06);
	lcd1602_write_0(0x0c);
	lcd1602_write_0(0x01);
	delay_lcd(2000);	
}