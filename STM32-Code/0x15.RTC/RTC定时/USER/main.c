#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"

void RTC_Configuration(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	RCC_LSEConfig(RCC_LSE_ON);
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	RCC_RTCCLKCmd(ENABLE);
	
	RTC_WaitForSynchro();
	RTC_WaitForLastTask();
	RTC_ITConfig(RTC_IT_SEC, ENABLE);
	
	RTC_WaitForLastTask();
	RTC_SetPrescaler(32767);
}


int main()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_LED_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00000);
	RTC_Configuration();
	while(1);
}

void RTC_IRQHandler(void)
{
	if(RTC_GetITStatus(RTC_IT_SEC) != RESET)
	{
		GPIOB->ODR ^= LED1_PIN;
		RTC_WaitForLastTask();
		RTC_ClearITPendingBit(RTC_IT_SEC);
	}
}



















