#include "stm32f10x.h"
#include "delay.h"
#include "core_cm3.h"




#if 0
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            /* Reload value impossible */
  
	//初始化reload寄存器的值
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      /* set reload register */
	
	//配置中断优先级，配置为15,默认为最低的优先级。
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Cortex-M0 System Interrupts */
	
	//初始化counter的值为0 
  SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
	
	//配置SystTick时钟为72Mhz
	//使能中断
	//使能sistick
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 
                   SysTick_CTRL_TICKINT_Msk   | 
                   SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
  return (0);                                                  /* Function successful */
}
#endif


void delay_us(uint32_t us) {
	uint16_t i = 0;
	SysTick_Config(72);
	for(i = 0; i < us ; i++) {
		while(!(SysTick->CTRL & 0x10000));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}


void delay_ms(uint32_t ms) {
	uint16_t i = 0;
	SysTick_Config(72000);
	for(i = 0; i < ms ; i++) {
		while(!(SysTick->CTRL & 0x10000));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}













