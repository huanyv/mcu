#include "hcsr04.h"
#include "delay.h"
#include "math.h"


void HC_SR04_GPIO_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
void HC_SR04_Start(void) {
	TRIG = 0;
	TRIG = 1;
	delay_us(20);
	TRIG = 0;
}
uint16_t HC_SR04ReadTime(void) {
	static uint16_t time = 0;
	uint16_t i = 0;
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;//准备读取数据
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	TIM2->CNT = 0;//TIM2中的计数器值清零
	i = 65535;
	while((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)&&(i > 10)){  // 防死等
		i--;
		delay_us(1);
	}
	if(i > 10) {
		TIM_Cmd(TIM2,ENABLE);//打开定时器
		i = 65535;
		while((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 1)&&(i > 10)) {    // 防死等
			i--;
			delay_us(1);
		}
		if(i > 10){
			TIM_Cmd(TIM2,DISABLE);//关闭定时器
			
			time = TIM2->CNT;//取时间 
		}
	}
	return time;
}
uint16_t HC_SR04ReadDistance(void) {
	uint16_t distance = 0;
	uint16_t time = 0;	
	HC_SR04_Start();
	time = HC_SR04ReadTime();
	distance = (time*0.034566)/2.0;
	return distance;
}


