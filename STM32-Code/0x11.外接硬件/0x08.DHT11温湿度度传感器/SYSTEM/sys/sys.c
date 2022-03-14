#include "sys.h"

/*******************************
*������־
*
*2019-4-23
*���뵥��GPIO�ĵ�ƽ��ת
*����Ե���GPIO��8λ����������Ӱ��ͬ��GPIO������IO���״̬
*
*2019-5-02
*��д λ������ ��
*
*2019-5-15
*������Զ� ϵͳ��ʼ�� ����
*
*******************************/

void Sys_Init(void) 
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // �ж����ȼ�����  2 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE); // �ָ�����Ĭ�Ϲ���    
	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); //   �ر�  JTAG  /*!<JTAG   PA15 PB3 PB4 */
	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE); // �ر�   JTAG  SWD  /*!<SWD   PA13 PA14  */
	
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






