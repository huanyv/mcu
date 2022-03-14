#include"stm32f10x.h"
#include"led.h"
#include"delay.h"
#include"timer.h"

#define A38 PBout(2)
#define B38 PBout(3)
#define C38 PBout(4)

uint8_t table1[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d, 
					0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; //共阴数码管 段选  码表
uint8_t  sec = 0;
uint16_t min = 0;

void display(void) {
	uint8_t i = 0;
	for(i = 0; i < 8; i++) {
		GPIO_Write(GPIOB,GPIO_ReadInputData(GPIOB) & 0X00ff);
		switch(i) {
			case 0:A38 = 0; B38 = 0; C38 = 0;
				GPIO_Write(GPIOB,GPIO_ReadInputData(GPIOB) | (table1[sec%10]<<8) );break;
			case 1:A38 = 1; B38 = 0; C38 = 0; 
				GPIO_Write(GPIOB,GPIO_ReadInputData(GPIOB) | (table1[sec/10]<<8) );break;			
			case 2:A38 = 0; B38 = 1; C38 = 0;                           
				break;                                                    
			case 3:A38 = 1; B38 = 1; C38 = 0;                           
				break;                                                    
			case 4:A38 = 0; B38 = 0; C38 = 1;                           
				GPIO_Write(GPIOB,GPIO_ReadInputData(GPIOB) | (table1[min%10]<<8) );break;
			case 5:A38 = 1; B38 = 0; C38 = 1;              
				GPIO_Write(GPIOB,GPIO_ReadInputData(GPIOB) | (table1[min/10%10]<<8) );break;
			case 6:A38 = 0; B38 = 1; C38 = 1;              
				GPIO_Write(GPIOB,GPIO_ReadInputData(GPIOB) | (table1[min/100%10]<<8) );break;
			case 7:A38 = 1; B38 = 1; C38 = 1;              
				GPIO_Write(GPIOB,GPIO_ReadInputData(GPIOB) | (table1[min/1000]<<8) );break;
		}
		delay_ms(1);
		GPIO_Write(GPIOB,GPIO_ReadInputData(GPIOB) & 0X00ff);
	}
}
int main(void) {
	LED_init();
	TIM2_Init(9999,7199);
	while(1) {
		display();
	}
}
void TIM2_IRQHandler(void) {
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == 1) {
		
		sec++;
		if(sec == 60){
			sec = 0;
			min++;
			if(min == 1000)
				min = 0;
		}
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}




