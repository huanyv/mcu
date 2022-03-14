 //  System   INCLUDE
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "rtc.h"

//  Hardware  INCLUDE
#include "led.h"
#include "key.h"
#include "LcdBsp.h"

int main(void) {	
	uint8_t tmp0;
	uint8_t tmp1;
	Sys_Init();
	USARTx_Init();
	LED_GPIO_Config();
	LCD_Init();
	RTC_Init();
	
	
	POINT_COLOR = RED;	
	LCD_ShowString(72,120,96,24,24,"  :  :  ");			
	POINT_COLOR = BLUE;
	LCD_ShowString(80,150,80,16,16,"    -  -  ");
	while(1) {
		
		if( tmp0 != calendar.sec )
		{
			tmp0 = calendar.sec;
			POINT_COLOR = RED;			
			LCD_ShowxNum(72,120,calendar.hour,2,24,0x00);
			LCD_ShowxNum(108,120,calendar.min,2,24,0x80);
			LCD_ShowxNum(144,120,calendar.sec,2,24,0x80);
			
			
			if( tmp1 != calendar.w_date ) 
			{
				tmp1 = calendar.w_date;
				POINT_COLOR = BLUE;			
				LCD_ShowxNum(80,150,calendar.w_year,4,16,0x80);
				LCD_ShowxNum(120,150,calendar.w_month,2,16,0x80);
				LCD_ShowxNum(144,150,calendar.w_date,2,16,0x80);
				
				POINT_COLOR = BLACK;
				switch(calendar.week)
				{
					case 0:LCD_ShowString(84,170,72,16,16,"  Sunday ");break;//
					case 1:LCD_ShowString(84,170,72,16,16,"  Monday ");break;//
					case 2:LCD_ShowString(84,170,72,16,16,"  Tuesday");break;//
					case 3:LCD_ShowString(84,170,72,16,16,"Wednesday");break;//
					case 4:LCD_ShowString(84,170,72,16,16," Thursday");break;//
					case 5:LCD_ShowString(84,170,72,16,16,"  Friday ");break;//
					case 6:LCD_ShowString(84,170,72,16,16," Saturday");break;//
				}
			}
			LED0 = ~LED0;
		}		
	} 
}













