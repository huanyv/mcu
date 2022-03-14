#include"pwm.h"
#include"delay.h"
#include"sys.h"
#include"int.h"

int main(void) {
    TIM3_PWM_Init(99,71);
  	INT_Init();

    while(1) {

        GPIOB->ODR ^= GPIO_Pin_0;
        delay_ms(500);

    }
}









