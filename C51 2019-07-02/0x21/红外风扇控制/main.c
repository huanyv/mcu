#include <reg52.h>
#include "sys.h"
#include "key.h"
#include "timer.h"
#include "infrared.h"
#include "18b20.h"
#include "lcd1602.h"

extern bit TEMP_CAP;
extern bit FLAG;    //   手动自动切换标志位
extern bit FLAG1;   //   启停标志位
extern uint speed;

int temp;

void display(void)
{
	float tp;
	if( TEMP_CAP == 1)
	{
		TEMP_CAP = 0;
		temp = readc();
		tp=temp;
		temp=tp*0.0625*10+0.5;
	}
	
	LCD_write_0(0x80);
	LCD_write_1('T');
	LCD_write_1('E');
	LCD_write_1('M');
	LCD_write_1('P');
	LCD_write_1(':');
	LCD_write_1(temp/100%10+'0');
	LCD_write_1(temp/10%10+'0');
	LCD_write_1('.');
	LCD_write_1(temp%10+'0');
	LCD_write_1('C');
	
	if( FLAG == 0 )
	{
		LCD_write_0(0x80+12);
		LCD_write_1(' ');
		LCD_write_1(' ');
		LCD_write_1(' ');
		LCD_write_1(' ');	
		LCD_write_0(0x80+12);
		LCD_write_1('H');
		LCD_write_1('A');
		LCD_write_1('N');
		LCD_write_1('D');		
	}
	else
	{
		LCD_write_0(0x80+12);
		LCD_write_1(' ');
		LCD_write_1(' ');
		LCD_write_1(' ');
		LCD_write_1(' ');	
		LCD_write_0(0x80+12);
		LCD_write_1('A');
		LCD_write_1('U');
		LCD_write_1('T');
		LCD_write_1('O');		
	}
	
	if( FLAG1 == 0 )
	{
		LCD_write_0(0xC0+11);
		LCD_write_1(' ');
		LCD_write_1(' ');
		LCD_write_1(' ');
		LCD_write_1(' ');		
		LCD_write_1(' ');	
		LCD_write_0(0xC0+11);
		LCD_write_1(' ');		
		LCD_write_1('S');
		LCD_write_1('T');
		LCD_write_1('O');
		LCD_write_1('P');		
	}
	else
	{
		LCD_write_0(0xC0+11);
		LCD_write_1(' ');
		LCD_write_1(' ');
		LCD_write_1(' ');
		LCD_write_1(' ');		
		LCD_write_1(' ');
		LCD_write_0(0xC0+11);
		LCD_write_1('S');
		LCD_write_1('T');
		LCD_write_1('A');
		LCD_write_1('R');		
		LCD_write_1('T');	
	}
	
	
}


void main(void)
{
	TIM_Init();
	IrInit();
	DS18B20_Init();
	LCD_init();
	while(1)
	{		
		if( FLAG == 0 )
		{
			KEY_Ctrl();
			Intrared_SPEED_Ctrl(); // 手动
		}
		else
		{
			if(temp<=250) // 自动
			{
				speed = 2;
			}
			else if( (temp>250)&&(temp<=300) )
			{
				speed = 5;
			}
			else if(temp>300)
			{
				speed = 10;
			}		
		}
		
		Intrared_MODE_Ctrl();		
		display();
		
	}	
}

