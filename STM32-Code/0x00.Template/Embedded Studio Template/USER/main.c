#include "stm32f10x.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"

#define LED1   PBout(0)
#define LED2   PBout(1)
#define LED3   PBout(2)

#define LED4   PCout(13)

#define KEY1   PAin(9)


int main(void) {
	GPIO_LED_Init();
        while(1) {
          LED2 = 0;
          LED1 = 0;
          LED3 = 0;
          delay_ms(500);
          LED2 = 1;
          LED1 = 1;
          LED3 = 1;
          delay_ms(500);
        }
}

