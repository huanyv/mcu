#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"

#if  0

int main(void) {
	uint32_t temp = 0;
	LED_init();
	My_USART_Init();
	TIM_Cap_Init(0xffff,71);
	while(1) {
		
		if(TIM2_CaptureStructure.Capture_State == 1) {
			
		temp = TIM2_CaptureStructure.Capture_Count*65536;
		
		temp = temp+TIM2_CaptureStructure.Capture_Value;
		
		
		printf("%d\n",temp);
		
	//	delay_ms(1000);
			
			TIM2_CaptureStructure.Capture_State = 0;
	
		}
		
		
		
		
//		
//		delay_ms(200);
//		
//		GPIOB->ODR ^= LED;
		
		
	}
}

#else
extern u8  TIM5CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值	
 int main(void)
 {		
 	u32 temp=0; 
	My_USART_Init();
 	LED_init();			     //LED端口初始化
 
 	TIM_Cap_Init(0XFFFF,72-1);	//以1Mhz的频率计数 
  while(1)
	{
 		delay_ms(10);
		TIM_SetCompare2(TIM2,TIM_GetCapture2(TIM2)+1);

		if(TIM_GetCapture2(TIM2)==300)TIM_SetCompare2(TIM2,0);	
		 		 
 		if(TIM5CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
		{
			temp=TIM5CH1_CAPTURE_STA&0X3F;
			temp*=65536;//溢出时间总和
			temp+=TIM5CH1_CAPTURE_VAL;//得到总的高电平时间
			printf("HIGH:%d us\r\n",temp);//打印总的高点平时间
			TIM5CH1_CAPTURE_STA=0;//开启下一次捕获
		}
	}
 }

#endif



