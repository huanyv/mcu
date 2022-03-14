#include "sys.h"


/*******************************
更新日志
2019-4-23
加入单个GPIO的电平翻转
加入对GPIO的8位操作，不会影响同GPIO的其它IO输出
2019-4-25
加入了JTAG和SWD的禁用


*******************************/

void NVIC_Configuration(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
}

void Disnable_SWD_JTAG(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);	// 禁用JTAG  PB3,PB4才可以当普通GPIO使用
	
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);//JTAG和SWD全部禁用，如果用SWD下载，请不要禁用  PB3,PB4,PA13,PA14
}

//   单个GPIO电平翻转
void GPIO_ReversePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->ODR ^= GPIO_Pin;
}

//以下为对 8 个 GPIO操作 ，不会影响同GPIO的其它IO输出
void GPIO_Low8BitWrite(GPIO_TypeDef *GPIOx,uint8_t dat) 
{
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

	GPIOx->ODR &= 0XFF00;
	GPIOx->ODR |= dat;
}
void GPIO_High8BitWrite(GPIO_TypeDef *GPIOx,uint8_t dat) 
{
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

	GPIOx->ODR &= 0X00FF;
	GPIOx->ODR |= (dat<<8);
}










