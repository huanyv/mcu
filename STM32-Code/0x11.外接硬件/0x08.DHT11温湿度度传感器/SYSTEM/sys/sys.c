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
*******************************/

void Sys_Init(void) 
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 中断优先级分组  2 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE); // 恢复引脚默认功能    
	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); //   关闭  JTAG  /*!<JTAG   PA15 PB3 PB4 */
	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE); // 关闭   JTAG  SWD  /*!<SWD   PA13 PA14  */
	
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






