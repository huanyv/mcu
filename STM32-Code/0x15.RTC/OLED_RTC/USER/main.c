 //  System   INCLUDE
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "rtc.h"
#include "i2c.h"

//  Hardware  INCLUDE
#include "led.h"
#include "key.h"
#include "oled_i2c.h"
#include "lunar_calendar.h"


extern const unsigned char CN_tab[][32];
extern const unsigned char BIG_Number[][32];
extern const unsigned char MONTH_Before[][32];

uint8_t timetab[] = "10:13:00";
/////////////////////0123456789
uint8_t datetab[] = "2019-06-12";

void dispaly1(void) {
	
	timetab[0] = calendar.hour/10+48;
	timetab[1] = calendar.hour%10+48;
	timetab[3] = calendar.min/10+48;
	timetab[4] = calendar.min%10+48;
	timetab[6] = calendar.sec/10+48;
	timetab[7] = calendar.sec%10+48;

	OLED_Show16x32(0,2,timetab); // 时间
	
}


void dispaly2(void) {
	int lunar_date[3] = {0};
	
	datetab[0] = calendar.w_year/1000+48;
	datetab[1] = calendar.w_year/100%10+48;
	datetab[2] = calendar.w_year/10%10+48;
	datetab[3] = calendar.w_year%10+48;
	datetab[5] = calendar.w_month/10+48;
	datetab[6] = calendar.w_month%10+48;
	datetab[8] = calendar.w_date/10+48;
	datetab[9] = calendar.w_date%10+48;
	
	RTC_Get(); // 更新时间
	
	OLED_ShowStr(0,0,datetab,2); // 日期
	
	OLED_ShowCN(80,0,2,CN_tab);
	OLED_ShowCN(96,0,3,CN_tab);
	if(calendar.week == 0)
		OLED_ShowCN(112,0,5,CN_tab); // 星期
	else
		OLED_ShowCN(112,0,calendar.week,BIG_Number); // 星期
	
	
	
	// 阴历转换
	zhuan_huan(calendar.w_year,calendar.w_month,calendar.w_date,lunar_date);
	
	if( lunar_date[0] == 0 ) {
		OLED_ShowCN(0,6,lunar_date[1],BIG_Number);
		OLED_ShowCN(16,6,4,CN_tab);
		
		if(lunar_date[2]==10) {
			OLED_ShowCN(32,6,0,MONTH_Before);
			OLED_ShowCN(48,6,0,BIG_Number);
		}
		else {
			OLED_ShowCN(32,6,lunar_date[2]/10,MONTH_Before);
			OLED_ShowCN(48,6,lunar_date[2]%10,BIG_Number);
		}
	}
	else {
		OLED_ShowCN(0,6,1,CN_tab);
		OLED_ShowCN(16,6,lunar_date[1],BIG_Number);
		OLED_ShowCN(32,6,4,CN_tab);
		
		if(lunar_date[2]==10) {
			OLED_ShowCN(48,6,0,MONTH_Before);
			OLED_ShowCN(64,6,0,BIG_Number);
		}
		else {
			OLED_ShowCN(48,6,lunar_date[2]/10,MONTH_Before);
			OLED_ShowCN(64,6,lunar_date[2]%10,BIG_Number);
		}
	}
	//printf("%d-%d\n\n",lunar_date[1],lunar_date[2]);
	
	 // //////节日
				/*  阳历
						元旦  清明  青年  建党  建军  教师  平安  圣诞
				*/	
	
	
	
	
	
	
	
	
	
				/*  阴历
						春节  中元  元宵  中秋  重阳  端午  腊八  七夕  小年  龙抬头
				*/
	
	
	
	
	
	
	
}
void KEY_Crtl(void) {
	static uint8_t KEY_LET_GO = 0;
	static uint8_t OLED_FLAG  = 0;
	if( (KEY0 == 0)&&(KEY_LET_GO == 0) ) {
		delay_ms(10);
		if(KEY0 == 0) {
			KEY_LET_GO = 1;
			calendar.sec++;
			if(calendar.sec == 60)calendar.sec = 0;
			RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
			
		}
	}
	if( (KEY1 == 0)&&(KEY_LET_GO == 0) ) {
		delay_ms(10);
		if(KEY1 == 0) {
			KEY_LET_GO = 1;
			if(OLED_FLAG == 0) {
				OLED_FLAG = 1;
				OLED_OFF();
			}
			else if(OLED_FLAG == 1) {
				OLED_FLAG = 0;
				OLED_ON();
			}
		}
	}
	if((KEY0 == 1)&&(KEY1 == 1)) {
		KEY_LET_GO = 0;
	}	
}


int main(void) {
	uint8_t temp1 = 0;
	uint8_t temp2 = 0;
	Sys_Init();
	//USARTx_Init();
	RTC_Init();
	LED_GPIO_Config();
	KEY_GPIO_Config();
	GPIO_I2C_Init();
	OLED_Init();
	
	while(1) {
		
		if(temp1 != calendar.sec) {
			temp1 = calendar.sec;			
			
			dispaly1();
			
			LED0 = !LED0;
		}
		
		if(temp2 != calendar.w_date) {
			temp2 = calendar.w_date;			
			
			dispaly2();
						
		}
		KEY_Crtl();
	} 
	
	
		
}



