#include "stm32f10x.h"
#include "delay.h"
#include "core_cm3.h"




#if 0
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            /* Reload value impossible */
  
	//��ʼ��reload�Ĵ�����ֵ
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      /* set reload register */
	
	//�����ж����ȼ�������Ϊ15,Ĭ��Ϊ��͵����ȼ���
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Cortex-M0 System Interrupts */
	
	//��ʼ��counter��ֵΪ0 
  SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
	
	//����SystTickʱ��Ϊ72Mhz
	//ʹ���ж�
	//ʹ��sistick
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













