#include "sys.h"

/*******************************
*更新日志
*
*2019-4-23
*加入单个GPIO的电平翻转
*加入对单组GPIO的8位操作，不会影响同组GPIO的其它IO输出状态
*
*2019-5-02
*自写 位带操作 宏
*
*2019-5-15
*添加了自定 系统初始化 函数
*
*2019-6-16
*添加快速初始化GPIO引脚函数以及宏
*******************************/

void Sys_Init(void) 
{
	SysTick->CTRL &= 0xFFFFFFFB; // SysTick 时钟为 HCLK/8
	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 中断优先级分组  2 
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE); // 恢复引脚默认功能    
	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); //   关闭  JTAG  /*!<JTAG   PA15 PB3 PB4 */
	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE); // 关闭   JTAG  SWD  /*!<SWD   PA13 PA14  */
}
 // 快速初始化GPIO
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
	
/*---------------------------------时钟配置-----------------------------------*/
  RCC_PERIPH_CLK_GPIO = ((uint32_t)(0x00000001<<((GPIOx_BASE&0x0000FFFF)>>10)));
  if( ((RCC->APB2ENR) & RCC_PERIPH_CLK_GPIO) == 0 )
  {
	RCC->APB2ENR |= RCC_PERIPH_CLK_GPIO; // 使能时钟
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

//单个GPIO电平翻转
void GPIO_ReversePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	assert_param(IS_GPIO_PIN(GPIO_Pin));

	GPIOx->ODR ^= GPIO_Pin;
}

//以下为对GPIO单独 8 位操作 ，不会影响同GPIO的其它IO输出
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






