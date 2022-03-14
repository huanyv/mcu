#include "sys.h"

/*******************************
更新日志

2019-4-23
加入单个GPIO的电平翻转
加入对GPIO的8位操作，不会影响同组GPIO的其它IO输出状态

2019-05-02
自写 位带操作 宏

*******************************/



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






