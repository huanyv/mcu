#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "rtc.h" 

Calendar_TypeDef calendar;//ʱ�ӽṹ�� 
 
 
 //�ж��Ƿ������꺯��
//�·�   1  2  3  4  5  6  7  8  9  10 11 12
//����   31 29 31 30 31 30 31 31 30 31 30 31
//������ 31 28 31 30 31 30 31 31 30 31 30 31
//����:���
//���:������ǲ�������.1,��.0,����
u8 Is_Leap_Year(u16 year)
{			  
	if(year%4==0) //�����ܱ�4����
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)return 1;//�����00��β,��Ҫ�ܱ�400���� 	   
			else return 0;   
		}else return 1;   
	}else return 0;	
}	 			   

 
//����ʱ��
//�������ʱ��ת��Ϊ����
//��1970��1��1��Ϊ��׼
//1970~2099��Ϊ�Ϸ����
//����ֵ:0,�ɹ�;����:�������.
//�·����ݱ�											 
u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //���������ݱ�	  
//ƽ����·����ڱ�
const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	u16 t;
	u32 seccount=0;
	if(syear<1970||syear>2099)return 1;	// ���Ϊ 1970-2099��
	for(t=1970;t<syear;t++)	//��������ݵ��������
	{
		if(Is_Leap_Year(t))seccount+=31622400;//�����������
		else seccount+=31536000;			  //ƽ���������
	}
	smon-=1;
	for(t=0;t<smon;t++)	   //��ǰ���·ݵ����������
	{
		seccount+=(u32)mon_table[t]*86400;//�·����������
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//����2�·�����һ���������	   
	}
	seccount+=(u32)(sday-1)*86400;//��ǰ�����ڵ���������� 
	seccount+=(u32)hour*3600;//Сʱ������
  seccount+=(u32)min*60;	 //����������
	seccount+=sec;//�������Ӽ���ȥ
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//ʹ��PWR��BKP����ʱ��  
	PWR_BackupAccessCmd(ENABLE);	//ʹ��RTC�ͺ󱸼Ĵ������� 
	
	RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������  	
	RTC_SetCounter(seccount);	//����RTC��������ֵ

	return 0;	    
}
 
 //��ʼ������		  
//��1970��1��1��Ϊ��׼
//1970~2099��Ϊ�Ϸ����
//syear,smon,sday,hour,min,sec�����ӵ�������ʱ����   
//����ֵ:0,�ɹ�;����:�������.
u8 RTC_Alarm_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	u16 t;
	u32 seccount=0;
	if(syear<1970||syear>2099)return 1;	   
	for(t=1970;t<syear;t++)	//��������ݵ��������
	{
		if(Is_Leap_Year(t))seccount+=31622400;//�����������
		else seccount+=31536000;			  //ƽ���������
	}
	smon-=1;
	for(t=0;t<smon;t++)	   //��ǰ���·ݵ����������
	{
		seccount+=(u32)mon_table[t]*86400;//�·����������
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//����2�·�����һ���������	   
	}
	seccount+=(u32)(sday-1)*86400;//��ǰ�����ڵ���������� 
	seccount+=(u32)hour*3600;//Сʱ������
  seccount+=(u32)min*60;	 //����������
	seccount+=sec;//�������Ӽ���ȥ 			    
	//����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//ʹ��PWR��BKP����ʱ��   
	PWR_BackupAccessCmd(ENABLE);	//ʹ�ܺ󱸼Ĵ�������  
	//���������Ǳ����!
	
	RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������  	
	RTC_SetAlarm(seccount);
	
	return 0;	    
}

 //�õ���ǰ��ʱ��
//����ֵ:0,�ɹ�;����:�������.
u8 RTC_Get(void)
{
	static u16 daycnt=0;
	u32 timecount=0;
	u32 temp=0;
	u16 temp1=0;	  
  timecount=RTC_GetCounter();
 	temp=timecount/86400;   //�õ�����(��������Ӧ��)
	if(daycnt!=temp)//����һ����
	{	  
		daycnt=temp;
		temp1=1970;	//��1970�꿪ʼ
		while(temp>=365)
		{				 
			if(Is_Leap_Year(temp1))//������
			{
				if(temp>=366)temp-=366;//�����������
				else {temp1++;break;}  
			}
			else temp-=365;	  //ƽ�� 
			temp1++;  
		}   
		calendar.w_year=temp1;//�õ����
		temp1=0;
		while(temp>=28)//������һ����
		{
			if(Is_Leap_Year(calendar.w_year)&&temp1==1)//�����ǲ�������/2�·�
			{
				if(temp>=29)temp-=29;//�����������
				else break; 
			}
			else 
			{
				if(temp>=mon_table[temp1])temp-=mon_table[temp1];//ƽ��
				else break;
			}
			temp1++;  
		}
		calendar.w_month=temp1+1;	//�õ��·�
		calendar.w_date=temp+1;  	//�õ����� 
	}
	temp=timecount%86400;     		//�õ�������   	   
	calendar.hour=temp/3600;     	//Сʱ
	calendar.min=(temp%3600)/60; 	//����	
	calendar.sec=(temp%3600)%60; 	//����
	calendar.week=RTC_Get_Week(calendar.w_year,calendar.w_month,calendar.w_date);//��ȡ����   
	return 0;
}
//������������ڼ�
//��������:���빫�����ڵõ�����(ֻ����1901-2099��)
//�������������������
//����ֵ�����ں�
u8 RTC_Get_Week(u16 year,u8 month,u8 day) // ���չ�ʽ 
{	
	u16 temp2;
	u8 yearH,yearL;
	
	yearH=year/100;	yearL=year%100; 
	// ���Ϊ21����,�������100  
	if (yearH>19)yearL+=100;
	// ����������ֻ��1900��֮���  
	temp2=yearL+yearL/4;
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7);
}			  

 
 static void RTC_NVIC_Config(void) {
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel                   = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_Init(&NVIC_InitStructure); // ��ʼ���ж�
 }
 
void RTC_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
	PWR_BackupAccessCmd(ENABLE); // ʹ��RTC�ͺ󱸼Ĵ����ķ���
	if(BKP_ReadBackupRegister(BKP_DR1) != 0x1111) {   // ����󱸼Ĵ����� Ԥдֵ����ʼ��RTC 
		BKP_DeInit(); // ��λ�󱸼Ĵ���
		RCC_LSEConfig(RCC_LSE_ON); // ���ⲿ����ʱ��
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET); // �ȴ� �ⲿ����ʱ���������
		
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); // ���� RTC ʱ��
		RCC_RTCCLKCmd(ENABLE); // ʹ�� RTC ���ⲿʱ�� �� ֻ���� RCC_RTCCLKConfig ��ſ����ô˺��� 
		
		RTC_WaitForSynchro(); // �ȴ� RTCʱ�� ͬ���ɹ� �� �ڲ��� RTC �ĺ���֮ǰ��Ҫ����һ��
		RTC_WaitForLastTask();  // ��ÿ��дRTC�Ĵ���֮ǰ����Ҫ���ô˺������ȴ���һ�εļĴ����������
		RTC_ITConfig(RTC_IT_SEC,ENABLE); // RTC�ж�����Ϊ���ж�
		
		RTC_WaitForLastTask(); // �ȴ���һ�εļĴ����������
		RTC_SetPrescaler(32767);  // ��Ƶ   32.768kHZ / (32767+1) = 1 s
	
		RTC_Set(2019,5,15,16,37,0); // ��ʼ��ʱ�䣬
		
		BKP_WriteBackupRegister(BKP_DR1,0x1111); // д�󱸼Ĵ���
	}
	else{ //���Ϊ��һ��Ԥдֵ �� ֱ�Ӷ�ȡʱ�伴��
		RTC_WaitForSynchro();	//�ȴ� RTC ͬ���ɹ� �� �ڲ��� RTC ����֮ǰ��Ҫ����һ��
		RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		RTC_ITConfig(RTC_IT_SEC, ENABLE);	//ʹ��RTC���ж�
	}
	
	RTC_NVIC_Config();

	RTC_Get(); // ����ʱ��
}


void RTC_IRQHandler(void) { // RTC�жϷ�����
	if(RTC_GetITStatus(RTC_IT_SEC) == 1) { // �����⵽���жϣ�Ҳ����1s��
		RTC_Get();   // ����ʱ��
		RTC_WaitForLastTask();
		RTC_ClearITPendingBit(RTC_IT_SEC); // ����жϱ�־λ	
	}
}
 
 







