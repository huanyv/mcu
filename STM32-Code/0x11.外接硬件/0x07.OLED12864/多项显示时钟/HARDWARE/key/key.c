#include "key.h"
#include "delay.h"
#include "ds1302.h"

/*

#define   SETTING     KEY1 //设置键
#define   ADJUST      KEY2 //调整时间

*/

uint8_t readdate_ctrl[]={0x81,0x83,0x85,0x8b,0x87,0x89,0x8d};
uint8_t writedate_ctrl[]={0x80,0x82,0x84,0x8a,0x86,0x88,0x8c};


uint8_t  MENU1 = 0;
uint8_t  MENU2 = 0;

uint8_t inverse[10];

void GPIO_KEY_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  =  KEY1_PIN|KEY2_PIN|KEY3_PIN|KEY4_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}


void INT_Init(void) {
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能时钟
	
	GPIO_KEY_Init();
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9 | GPIO_PinSource10);//中断线映射
	
	EXTI_InitStructure.EXTI_Line		= EXTI_Line9 | EXTI_Line10;//要使能的 中断线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;///使能
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;//中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	EXTI_Init(&EXTI_InitStructure);//外部中断初始化
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel									 = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd								 = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
	NVIC_Init(&NVIC_InitStructure);//配置中断9 优先级
	
	NVIC_InitStructure.NVIC_IRQChannel									 = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd								 = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
	NVIC_Init(&NVIC_InitStructure);//配置中断10 优先级
}

void EXTI9_5_IRQHandler(void) {
	delay_ms(20);
	if(EXTI_GetITStatus(EXTI_Line9) == 1)
	{
		if(SETTING == 0)
			MENU1++;
	}
	EXTI_ClearITPendingBit(EXTI_Line9);
}
void EXTI15_10_IRQHandler(void) {
	uint8_t temp;
	delay_ms(20);
	if(EXTI_GetITStatus(EXTI_Line10) == 1)
	{
		if(ADJUST == 0) {
			if(MENU1>0&&MENU1<8) {		
				temp=Read_DS1302(readdate_ctrl[MENU1-1]);
				temp++;
				if((temp&0x0f)>9)
				{
					temp=temp+6;
				}
				if(MENU1==1||MENU1==2)		   
				{
					if(temp==0x60)	   //秒和分最大60
					{
						temp=0x00;
					}
				}
				if(MENU1==3)
				{
					if(temp==0x24)	 //小时最大24
					{
						temp=0x00;
					}
				}
				if(MENU1==4)
				{
					if(temp==0x08)	//星期最大  7
					{
						temp=0x01;
					}
				}
				if(MENU1==5)
				{
					if(temp==0x32)	 //日  最大31
					{
						temp=0x01;
					}
				}
				if(MENU1==6)
				{
					if(temp==0x13)		//月最大12
					{
						temp=0x01;
					}
				}
				if(MENU1==7)
				{
					if(temp==0x31)	//以便 易调  年最大暂时设为  30
					{
						temp=0x01;
					}
				}
				Write_DS1302(0x8e,0x00);
				Write_DS1302(writedate_ctrl[MENU1-1],(temp));
				Write_DS1302(0x8e,0x80);
			}		
		}
			
	}
	EXTI_ClearITPendingBit(EXTI_Line10);
}



