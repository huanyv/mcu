#include "sys.h"


/*******************************
������־
2019-4-23
���뵥��GPIO�ĵ�ƽ��ת
�����GPIO��8λ����������Ӱ��ͬGPIO������IO���
2019-4-25
������JTAG��SWD�Ľ���


*******************************/

void NVIC_Configuration(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
}

void Disnable_SWD_JTAG(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);	// ����JTAG  PB3,PB4�ſ��Ե���ͨGPIOʹ��
	
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);//JTAG��SWDȫ�����ã������SWD���أ��벻Ҫ����  PB3,PB4,PA13,PA14
}

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










