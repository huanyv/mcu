#include "sys.h"



void NVIC_Configuration(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
}


//   单个GPIO电平翻转
void GPIO_ReversePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->ODR ^= GPIO_Pin;
}

//以下为对 8 个 GPIO操作 ，不会影响同GPIO的其它IO输出
void GPIO_LowWrite(GPIO_TypeDef *GPIOx,uint8_t dat) 
{
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

	GPIOx->ODR &= 0XFF00;
	GPIOx->ODR |= dat;
}
void GPIO_HighWrite(GPIO_TypeDef *GPIOx,uint8_t dat) 
{
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

	GPIOx->ODR &= 0X00FF;
	GPIOx->ODR |= (dat<<8);
}












