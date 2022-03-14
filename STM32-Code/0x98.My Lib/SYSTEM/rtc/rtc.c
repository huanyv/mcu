#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "rtc.h" 

Calendar_TypeDef calendar;//时钟结构体 
 
 
 //判断是否是闰年函数
//月份   1  2  3  4  5  6  7  8  9  10 11 12
//闰年   31 29 31 30 31 30 31 31 30 31 30 31
//非闰年 31 28 31 30 31 30 31 31 30 31 30 31
//输入:年份
//输出:该年份是不是闰年.1,是.0,不是
u8 Is_Leap_Year(u16 year)
{			  
	if(year%4==0) //必须能被4整除
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)return 1;//如果以00结尾,还要能被400整除 	   
			else return 0;   
		}else return 1;   
	}else return 0;	
}	 			   

 
//设置时钟
//把输入的时钟转换为秒钟
//以1970年1月1日为基准
//1970~2099年为合法年份
//返回值:0,成功;其他:错误代码.
//月份数据表											 
u8 const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //月修正数据表	  
//平年的月份日期表
const u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	u16 t;
	u32 seccount=0;
	if(syear<1970||syear>2099)return 1;	// 年份为 1970-2099年
	for(t=1970;t<syear;t++)	//把所有年份的秒钟相加
	{
		if(Is_Leap_Year(t))seccount+=31622400;//闰年的秒钟数
		else seccount+=31536000;			  //平年的秒钟数
	}
	smon-=1;
	for(t=0;t<smon;t++)	   //把前面月份的秒钟数相加
	{
		seccount+=(u32)mon_table[t]*86400;//月份秒钟数相加
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//闰年2月份增加一天的秒钟数	   
	}
	seccount+=(u32)(sday-1)*86400;//把前面日期的秒钟数相加 
	seccount+=(u32)hour*3600;//小时秒钟数
  seccount+=(u32)min*60;	 //分钟秒钟数
	seccount+=sec;//最后的秒钟加上去
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//使能PWR和BKP外设时钟  
	PWR_BackupAccessCmd(ENABLE);	//使能RTC和后备寄存器访问 
	
	RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成  	
	RTC_SetCounter(seccount);	//设置RTC计数器的值

	return 0;	    
}
 
 //初始化闹钟		  
//以1970年1月1日为基准
//1970~2099年为合法年份
//syear,smon,sday,hour,min,sec：闹钟的年月日时分秒   
//返回值:0,成功;其他:错误代码.
u8 RTC_Alarm_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec)
{
	u16 t;
	u32 seccount=0;
	if(syear<1970||syear>2099)return 1;	   
	for(t=1970;t<syear;t++)	//把所有年份的秒钟相加
	{
		if(Is_Leap_Year(t))seccount+=31622400;//闰年的秒钟数
		else seccount+=31536000;			  //平年的秒钟数
	}
	smon-=1;
	for(t=0;t<smon;t++)	   //把前面月份的秒钟数相加
	{
		seccount+=(u32)mon_table[t]*86400;//月份秒钟数相加
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//闰年2月份增加一天的秒钟数	   
	}
	seccount+=(u32)(sday-1)*86400;//把前面日期的秒钟数相加 
	seccount+=(u32)hour*3600;//小时秒钟数
  seccount+=(u32)min*60;	 //分钟秒钟数
	seccount+=sec;//最后的秒钟加上去 			    
	//设置时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//使能PWR和BKP外设时钟   
	PWR_BackupAccessCmd(ENABLE);	//使能后备寄存器访问  
	//上面三步是必须的!
	
	RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成  	
	RTC_SetAlarm(seccount);
	
	return 0;	    
}

 //得到当前的时间
//返回值:0,成功;其他:错误代码.
u8 RTC_Get(void)
{
	static u16 daycnt=0;
	u32 timecount=0;
	u32 temp=0;
	u16 temp1=0;	  
  timecount=RTC_GetCounter();
 	temp=timecount/86400;   //得到天数(秒钟数对应的)
	if(daycnt!=temp)//超过一天了
	{	  
		daycnt=temp;
		temp1=1970;	//从1970年开始
		while(temp>=365)
		{				 
			if(Is_Leap_Year(temp1))//是闰年
			{
				if(temp>=366)temp-=366;//闰年的秒钟数
				else {temp1++;break;}  
			}
			else temp-=365;	  //平年 
			temp1++;  
		}   
		calendar.w_year=temp1;//得到年份
		temp1=0;
		while(temp>=28)//超过了一个月
		{
			if(Is_Leap_Year(calendar.w_year)&&temp1==1)//当年是不是闰年/2月份
			{
				if(temp>=29)temp-=29;//闰年的秒钟数
				else break; 
			}
			else 
			{
				if(temp>=mon_table[temp1])temp-=mon_table[temp1];//平年
				else break;
			}
			temp1++;  
		}
		calendar.w_month=temp1+1;	//得到月份
		calendar.w_date=temp+1;  	//得到日期 
	}
	temp=timecount%86400;     		//得到秒钟数   	   
	calendar.hour=temp/3600;     	//小时
	calendar.min=(temp%3600)/60; 	//分钟	
	calendar.sec=(temp%3600)%60; 	//秒钟
	calendar.week=RTC_Get_Week(calendar.w_year,calendar.w_month,calendar.w_date);//获取星期   
	return 0;
}
//获得现在是星期几
//功能描述:输入公历日期得到星期(只允许1901-2099年)
//输入参数：公历年月日
//返回值：星期号
u8 RTC_Get_Week(u16 year,u8 month,u8 day) // 蔡勒公式 
{	
	u16 temp2;
	u8 yearH,yearL;
	
	yearH=year/100;	yearL=year%100; 
	// 如果为21世纪,年份数加100  
	if (yearH>19)yearL+=100;
	// 所过闰年数只算1900年之后的  
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
	NVIC_Init(&NVIC_InitStructure); // 初始化中断
 }
 
void RTC_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
	PWR_BackupAccessCmd(ENABLE); // 使能RTC和后备寄存器的访问
	if(BKP_ReadBackupRegister(BKP_DR1) != 0x1111) {   // 如果后备寄存器非 预写值，初始化RTC 
		BKP_DeInit(); // 复位后备寄存器
		RCC_LSEConfig(RCC_LSE_ON); // 打开外部低速时钟
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET); // 等待 外部低速时钟配置完成
		
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); // 配置 RTC 时钟
		RCC_RTCCLKCmd(ENABLE); // 使能 RTC 的外部时钟 ， 只有在 RCC_RTCCLKConfig 后才可以用此函数 
		
		RTC_WaitForSynchro(); // 等待 RTC时钟 同步成功 ， 在操作 RTC 的函数之前需要调用一次
		RTC_WaitForLastTask();  // 在每次写RTC寄存器之前，都要调用此函数，等待上一次的寄存器配置完成
		RTC_ITConfig(RTC_IT_SEC,ENABLE); // RTC中断配置为秒中断
		
		RTC_WaitForLastTask(); // 等待上一次的寄存器配置完成
		RTC_SetPrescaler(32767);  // 分频   32.768kHZ / (32767+1) = 1 s
	
		RTC_Set(2019,5,15,16,37,0); // 初始化时间，
		
		BKP_WriteBackupRegister(BKP_DR1,0x1111); // 写后备寄存器
	}
	else{ //如果为上一次预写值 ， 直接读取时间即可
		RTC_WaitForSynchro();	//等待 RTC 同步成功 ， 在操作 RTC 函数之前需要调用一次
		RTC_WaitForLastTask();	//等待最近一次对RTC寄存器的写操作完成
		RTC_ITConfig(RTC_IT_SEC, ENABLE);	//使能RTC秒中断
	}
	
	RTC_NVIC_Config();

	RTC_Get(); // 更新时间
}


void RTC_IRQHandler(void) { // RTC中断服务函数
	if(RTC_GetITStatus(RTC_IT_SEC) == 1) { // 如果检测到秒中断，也就是1s后
		RTC_Get();   // 更新时间
		RTC_WaitForLastTask();
		RTC_ClearITPendingBit(RTC_IT_SEC); // 清除中断标志位	
	}
}
 
 







