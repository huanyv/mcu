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
extern u8  TIM5CH1_CAPTURE_STA;		//���벶��״̬		    				
extern u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ	
 int main(void)
 {		
 	u32 temp=0; 
	My_USART_Init();
 	LED_init();			     //LED�˿ڳ�ʼ��
 
 	TIM_Cap_Init(0XFFFF,72-1);	//��1Mhz��Ƶ�ʼ��� 
  while(1)
	{
 		delay_ms(10);
		TIM_SetCompare2(TIM2,TIM_GetCapture2(TIM2)+1);

		if(TIM_GetCapture2(TIM2)==300)TIM_SetCompare2(TIM2,0);	
		 		 
 		if(TIM5CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
		{
			temp=TIM5CH1_CAPTURE_STA&0X3F;
			temp*=65536;//���ʱ���ܺ�
			temp+=TIM5CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
			printf("HIGH:%d us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
			TIM5CH1_CAPTURE_STA=0;//������һ�β���
		}
	}
 }

#endif



