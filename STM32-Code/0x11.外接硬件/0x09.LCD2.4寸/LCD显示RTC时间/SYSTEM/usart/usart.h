#ifndef _USART_H_
#define _USART_H_
#include "sys.h" 
#include <stdio.h>

 // �Ƿ�ʹ�ܴ����ж�
#define       USART_IT_EN                    0


#define       USARTX                         USART1

 // ����GPIO�ĺ�
#define       USARTX_GPIO_CLK                RCC_APB2Periph_GPIOA
#define       USARTX_GPIO                    GPIOA
#define       USARTX_TX_PIN                  GPIO_Pin_9  // TX GPIO
#define       USARTX_RX_PIN                  GPIO_Pin_10 // RX GPIO

 // �������õĺ�
#define       USARTX_PERIPH_APBx_CLK_CMD     RCC_APB2PeriphClockCmd
#define       USARTX_PERIPH_CLK              RCC_APB2Periph_USART1
#define       USARTX_BAUD                    115200

 // �����ж����ú�
#define       USARTX_IT_CHANNL               USART1_IRQn
#define       USARTX_IT_CONFIG               USART_IT_RXNE
#define       USARTX_IT_FUNCTION             USART1_IRQHandler



void USARTx_Init(void);


#endif


