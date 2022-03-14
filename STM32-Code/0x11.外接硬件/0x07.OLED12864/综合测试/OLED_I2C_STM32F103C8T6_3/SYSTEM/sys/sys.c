#include "sys.h"

/*******************************
������־

2019-4-23
���뵥��GPIO�ĵ�ƽ��ת
�����GPIO��8λ����������Ӱ��ͬ��GPIO������IO���״̬

2019-05-02
��д λ������ ��

*******************************/



//   ����GPIO��ƽ��ת
void GPIO_ReversePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_Pin));

	GPIOx->ODR ^= GPIO_Pin;
}

//����Ϊ�� 8 �� GPIO���� ������Ӱ��ͬGPIO������IO���
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






