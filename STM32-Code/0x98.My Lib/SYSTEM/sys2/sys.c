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
*2019-6-16
*��ӿ��ٳ�ʼ��GPIO���ź����Լ���
*******************************/

void Sys_Init(void) 
{
	SysTick->CTRL &= 0xFFFFFFFB; // SysTick ʱ��Ϊ HCLK/8
	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // �ж����ȼ�����  2 
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE); // �ָ�����Ĭ�Ϲ���    
	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); //   �ر�  JTAG  /*!<JTAG   PA15 PB3 PB4 */
	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE); // �ر�   JTAG  SWD  /*!<SWD   PA13 PA14  */
}
 // ���ٳ�ʼ��GPIO
void GPIO_Pin_Config(uint32_t Pxx, uint8_t GPIO_MODE)
{
  uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00;
  uint32_t tmpreg = 0x00, pinmask = 0x00;
  
  GPIO_TypeDef* GPIOx;
  uint32_t GPIOx_BASE;uint32_t RCC_PERIPH_CLK_GPIO;uint16_t GPIO_Pin;
	
  /* Check the parameters */
  assert_param(IS_Pxx_PERIPH(Pxx));
  assert_param(IS_GPIO_MODE_PERIPH(GPIO_MODE));
	
  GPIOx_BASE = ((Pxx & 0xFFFF0000)>>16)|APB2PERIPH_BASE;
  GPIOx = ((GPIO_TypeDef *)GPIOx_BASE);
  GPIO_Pin = ((uint16_t)(Pxx & 0x0000FFFF));
	
/*---------------------------------ʱ������-----------------------------------*/
  RCC_PERIPH_CLK_GPIO = ((uint32_t)(0x00000001<<((GPIOx_BASE&0x0000FFFF)>>10)));
  if( ((RCC->APB2ENR) & RCC_PERIPH_CLK_GPIO) == 0 )
  {
	RCC->APB2ENR |= RCC_PERIPH_CLK_GPIO; // ʹ��ʱ��
  }
  
/*---------------------------- GPIO Mode Configuration -----------------------*/
  currentmode = ((uint32_t)GPIO_MODE) & ((uint32_t)0x0F);
  if ((((uint32_t)GPIO_MODE) & ((uint32_t)0x10)) != 0x00) 
	{
    currentmode |= ((uint32_t)GPIO_Speed_50MHz);
  }
/*---------------------------- GPIO CRL Configuration ------------------------*/
  /* Configure the eight low port pins */
  if (((uint32_t)GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
  {
    tmpreg = GPIOx->CRL;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = ((uint32_t)0x01) << pinpos;
      /* Get the port pins position */
      currentpin = (GPIO_Pin) & pos;
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding low control register bits */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);
        /* Reset the corresponding ODR bit */
        if (GPIO_MODE == GPIO_MODE_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << pinpos);
        }
        else
        {
          /* Set the corresponding ODR bit */
          if (GPIO_MODE == GPIO_MODE_IPU)
          {
            GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
          }
        }
      }
    }
    GPIOx->CRL = tmpreg;
  }
/*---------------------------- GPIO CRH Configuration ------------------------*/
  /* Configure the eight high port pins */
  if (GPIO_Pin > 0x00FF)
  {
    tmpreg = GPIOx->CRH;
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = (((uint32_t)0x01) << (pinpos + 0x08));
      /* Get the port pins position */
      currentpin = ((GPIO_Pin) & pos);
      if (currentpin == pos)
      {
        pos = pinpos << 2;
        /* Clear the corresponding high control register bits */
        pinmask = ((uint32_t)0x0F) << pos;
        tmpreg &= ~pinmask;
        /* Write the mode configuration in the corresponding bits */
        tmpreg |= (currentmode << pos);
        /* Reset the corresponding ODR bit */
        if (GPIO_MODE == GPIO_MODE_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
        /* Set the corresponding ODR bit */
        if (GPIO_MODE == GPIO_MODE_IPU)
        {
          GPIOx->BSRR = (((uint32_t)0x01) << (pinpos + 0x08));
        }
      }
    }
    GPIOx->CRH = tmpreg;
  }
}

//����GPIO��ƽ��ת
void GPIO_ReversePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_Pin));

	GPIOx->ODR ^= GPIO_Pin;
}

//����Ϊ��GPIO���� 8 λ���� ������Ӱ��ͬGPIO������IO���
void GPIO_Low8BitWrite(GPIO_TypeDef *GPIOx,uint8_t dat) 
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

	GPIOx->ODR &= 0XFF00;
	GPIOx->ODR |= dat;
}
void GPIO_High8BitWrite(GPIO_TypeDef *GPIOx,uint8_t dat)
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

	GPIOx->ODR &= 0X00FF;
	GPIOx->ODR |= (dat<<8);
}






