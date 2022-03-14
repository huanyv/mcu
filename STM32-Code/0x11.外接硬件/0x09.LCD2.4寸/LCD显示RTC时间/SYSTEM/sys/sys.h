#ifndef __SYS_H
#define __SYS_H
#include "stm32f10x.h"

/*********************************************
SRAM
AliasAddr=0x22000000+((A-0x20000000)*8+n)*4
相当于
AliasAddr=0x22000000+(A-0x20000000)*32+n*4

片上外设
AliasAddr=0x42000000+((A-0x40000000)*8+n)*4
相当于
AliasAddr=0x42000000+(A-0x40000000)*32+n*4
*********************************************/

#define    BIT_BANG(addr,n)        (addr & 0XF0000000)+0X02000000+((addr & 0x00FFFFFF)<<5)+(n<<2)//将膨胀的地址转换为 二进制
#define    MANDATORY_Addr(addr)    *((volatile uint32_t *)(addr))//地址转换宏
#define    BIT_ADDR(addr,n)        MANDATORY_Addr(BIT_BANG(addr,n))//将膨胀的地址转换为的二进制转换成地址

/************************************************************************************************
GPIOx_BASE是 ST 库中已经定义好的宏，在 stm32f0x.h 中。
是GPIOx的起始地址

stm32f0x.h 内部写法
#define PERIPH_BASE           ((uint32_t)0x40000000)   //  外设的基地址 // !< Peripheral base address in the alias region 
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)  //APB2总线上 外设 的相对基地址的偏移量
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800) //  GPIOA  相对 APB2总线 的地址偏移
*************************************************************************************************/

//获取ODR寄存器的地址，ODR寄存器偏移量：0x0C
#define    GPIOA_ODR_Addr    (GPIOA_BASE+0X0C)
#define    GPIOB_ODR_Addr    (GPIOB_BASE+0X0C)
#define    GPIOC_ODR_Addr    (GPIOC_BASE+0X0C)
#define    GPIOD_ODR_Addr    (GPIOD_BASE+0X0C)
#define    GPIOE_ODR_Addr    (GPIOE_BASE+0X0C)
#define    GPIOF_ODR_Addr    (GPIOF_BASE+0X0C)
#define    GPIOG_ODR_Addr    (GPIOG_BASE+0X0C)

//获取IDR寄存器的地址，IDR寄存器偏移量：0x08
#define    GPIOA_IDR_Addr    (GPIOA_BASE+0X08)
#define    GPIOB_IDR_Addr    (GPIOB_BASE+0X08)
#define    GPIOC_IDR_Addr    (GPIOC_BASE+0X08)
#define    GPIOD_IDR_Addr    (GPIOD_BASE+0X08)
#define    GPIOE_IDR_Addr    (GPIOE_BASE+0X08)
#define    GPIOF_IDR_Addr    (GPIOF_BASE+0X08)
#define    GPIOG_IDR_Addr    (GPIOG_BASE+0X08)

//  位定义
//  Pxout  输入
//  Pxin   输出
#define    PAout(n)     BIT_ADDR(GPIOA_ODR_Addr,n)
#define    PAin(n)      BIT_ADDR(GPIOA_IDR_Addr,n)

#define    PBout(n)     BIT_ADDR(GPIOB_ODR_Addr,n)
#define    PBin(n)      BIT_ADDR(GPIOB_IDR_Addr,n)

#define    PCout(n)     BIT_ADDR(GPIOC_ODR_Addr,n)
#define    PCin(n)      BIT_ADDR(GPIOC_IDR_Addr,n)

#define    PDout(n)     BIT_ADDR(GPIOD_ODR_Addr,n)
#define    PDin(n)      BIT_ADDR(GPIOD_IDR_Addr,n)

#define    PEout(n)     BIT_ADDR(GPIOE_ODR_Addr,n)
#define    PEin(n)      BIT_ADDR(GPIOE_IDR_Addr,n)

#define    PFout(n)     BIT_ADDR(GPIOF_ODR_Addr,n)
#define    PFin(n)      BIT_ADDR(GPIOF_IDR_Addr,n)

#define    PGout(n)     BIT_ADDR(GPIOG_ODR_Addr,n)
#define    PGin(n)      BIT_ADDR(GPIOG_IDR_Addr,n)

 // GPIOA
#define    PA0          ((uint32_t)0x08000001) // GPIO相对总线的偏移地址 + 引脚定义
#define    PA1          ((uint32_t)0x08000002)
#define    PA2          ((uint32_t)0x08000004)
#define    PA3          ((uint32_t)0x08000008)
#define    PA4          ((uint32_t)0x08000010)
#define    PA5          ((uint32_t)0x08000020)
#define    PA6          ((uint32_t)0x08000040)
#define    PA7          ((uint32_t)0x08000080)
#define    PA8          ((uint32_t)0x08000100)
#define    PA9          ((uint32_t)0x08000200)
#define    PA10         ((uint32_t)0x08000400)
#define    PA11         ((uint32_t)0x08000800)
#define    PA12         ((uint32_t)0x08001000)
#define    PA13         ((uint32_t)0x08002000)
#define    PA14         ((uint32_t)0x08004000)
#define    PA15         ((uint32_t)0x08008000)
#define    PA0_15       ((uint32_t)0x0800FFFF)
 // GPIOB
#define    PB0          ((uint32_t)0x0C000001)
#define    PB1          ((uint32_t)0x0C000002)
#define    PB2          ((uint32_t)0x0C000004)
#define    PB3          ((uint32_t)0x0C000008)
#define    PB4          ((uint32_t)0x0C000010)
#define    PB5          ((uint32_t)0x0C000020)
#define    PB6          ((uint32_t)0x0C000040)
#define    PB7          ((uint32_t)0x0C000080)
#define    PB8          ((uint32_t)0x0C000100)
#define    PB9          ((uint32_t)0x0C000200)
#define    PB10         ((uint32_t)0x0C000400)
#define    PB11         ((uint32_t)0x0C000800)
#define    PB12         ((uint32_t)0x0C001000)
#define    PB13         ((uint32_t)0x0C002000)
#define    PB14         ((uint32_t)0x0C004000)
#define    PB15         ((uint32_t)0x0C008000)
#define    PB0_15       ((uint32_t)0x0C00FFFF)
 // GPIOC
#define    PC0          ((uint32_t)0x10000001)
#define    PC1          ((uint32_t)0x10000002)
#define    PC2          ((uint32_t)0x10000004)
#define    PC3          ((uint32_t)0x10000008)
#define    PC4          ((uint32_t)0x10000010)
#define    PC5          ((uint32_t)0x10000020)
#define    PC6          ((uint32_t)0x10000040)
#define    PC7          ((uint32_t)0x10000080)
#define    PC8          ((uint32_t)0x10000100)
#define    PC9          ((uint32_t)0x10000200)
#define    PC10         ((uint32_t)0x10000400)
#define    PC11         ((uint32_t)0x10000800)
#define    PC12         ((uint32_t)0x10001000)
#define    PC13         ((uint32_t)0x10002000)
#define    PC14         ((uint32_t)0x10004000)
#define    PC15         ((uint32_t)0x10008000)
#define    PC0_15       ((uint32_t)0x1000FFFF)
 // GPIOD
#define    PD0          ((uint32_t)0x14000001)
#define    PD1          ((uint32_t)0x14000002)
#define    PD2          ((uint32_t)0x14000004)
#define    PD3          ((uint32_t)0x14000008)
#define    PD4          ((uint32_t)0x14000010)
#define    PD5          ((uint32_t)0x14000020)
#define    PD6          ((uint32_t)0x14000040)
#define    PD7          ((uint32_t)0x14000080)
#define    PD8          ((uint32_t)0x14000100)
#define    PD9          ((uint32_t)0x14000200)
#define    PD10         ((uint32_t)0x14000400)
#define    PD11         ((uint32_t)0x14000800)
#define    PD12         ((uint32_t)0x14001000)
#define    PD13         ((uint32_t)0x14002000)
#define    PD14         ((uint32_t)0x14004000)
#define    PD15         ((uint32_t)0x14008000)
#define    PD0_15       ((uint32_t)0x1400FFFF)
 // GPIOE
#define    PE0          ((uint32_t)0x18000001)
#define    PE1          ((uint32_t)0x18000002)
#define    PE2          ((uint32_t)0x18000004)
#define    PE3          ((uint32_t)0x18000008)
#define    PE4          ((uint32_t)0x18000010)
#define    PE5          ((uint32_t)0x18000020)
#define    PE6          ((uint32_t)0x18000040)
#define    PE7          ((uint32_t)0x18000080)
#define    PE8          ((uint32_t)0x18000100)
#define    PE9          ((uint32_t)0x18000200)
#define    PE10         ((uint32_t)0x18000400)
#define    PE11         ((uint32_t)0x18000800)
#define    PE12         ((uint32_t)0x18001000)
#define    PE13         ((uint32_t)0x18002000)
#define    PE14         ((uint32_t)0x18004000)
#define    PE15         ((uint32_t)0x18008000)
#define    PE0_15       ((uint32_t)0x1800FFFF)
 // GPIOF
#define    PF0          ((uint32_t)0x1C000001)
#define    PF1          ((uint32_t)0x1C000002)
#define    PF2          ((uint32_t)0x1C000004)
#define    PF3          ((uint32_t)0x1C000008)
#define    PF4          ((uint32_t)0x1C000010)
#define    PF5          ((uint32_t)0x1C000020)
#define    PF6          ((uint32_t)0x1C000040)
#define    PF7          ((uint32_t)0x1C000080)
#define    PF8          ((uint32_t)0x1C000100)
#define    PF9          ((uint32_t)0x1C000200)
#define    PF10         ((uint32_t)0x1C000400)
#define    PF11         ((uint32_t)0x1C000800)
#define    PF12         ((uint32_t)0x1C001000)
#define    PF13         ((uint32_t)0x1C002000)
#define    PF14         ((uint32_t)0x1C004000)
#define    PF15         ((uint32_t)0x1C008000)
#define    PF0_15       ((uint32_t)0x1C00FFFF)
 // GPIOG
#define    PG0          ((uint32_t)0x20000001)
#define    PG1          ((uint32_t)0x20000002)
#define    PG2          ((uint32_t)0x20000004)
#define    PG3          ((uint32_t)0x20000008)
#define    PG4          ((uint32_t)0x20000010)
#define    PG5          ((uint32_t)0x20000020)
#define    PG6          ((uint32_t)0x20000040)
#define    PG7          ((uint32_t)0x20000080)
#define    PG8          ((uint32_t)0x20000100)
#define    PG9          ((uint32_t)0x20000200)
#define    PG10         ((uint32_t)0x20000400)
#define    PG11         ((uint32_t)0x20000800)
#define    PG12         ((uint32_t)0x20001000)
#define    PG13         ((uint32_t)0x20002000)
#define    PG14         ((uint32_t)0x20004000)
#define    PG15         ((uint32_t)0x20008000)
#define    PG0_15       ((uint32_t)0x2000FFFF)
#define IS_Pxx_PERIPH(Pxx) (((Pxx) == PA0--PA15) || \
                            ((Pxx) == PB0--PB15) || \
                            ((Pxx) == PC0--PC15) || \
                            ((Pxx) == PD0--PD15) || \
                            ((Pxx) == PE0--PE15) || \
                            ((Pxx) == PF0--PF15) || \
                            ((Pxx) == PG0--PG15))

#define       GPIO_MODE_AIN           ((uint8_t)0x00)    //模拟输入
#define       GPIO_MODE_IN_FLOATING   ((uint8_t)0x04)    //浮空输入
#define       GPIO_MODE_IPD           ((uint8_t)0x28)    //下拉输入
#define       GPIO_MODE_IPU           ((uint8_t)0x48)    //上拉输入
#define       GPIO_MODE_OUT_OD        ((uint8_t)0x14)    //开漏输出
#define       GPIO_MODE_OUT_PP        ((uint8_t)0x10)    //推挽输出
#define       GPIO_MODE_AF_OD         ((uint8_t)0x1C)    //复用开漏输出
#define       GPIO_MODE_AF_PP         ((uint8_t)0x18)    //复用推挽输出
#define       OUTPUT                  GPIO_MODE_OUT_PP // 默认输出 为推挽输出
#define       INPUT                   GPIO_MODE_IPU    // 默认输入 为上拉输入
#define IS_GPIO_MODE_PERIPH(MODE) (((MODE) == GPIO_MODE_AIN)    || ((MODE) == GPIO_MODE_IN_FLOATING) || \
                                   ((MODE) == GPIO_MODE_IPD)    || ((MODE) == GPIO_MODE_IPU)         || \
                                   ((MODE) == GPIO_MODE_OUT_OD) || ((MODE) == GPIO_MODE_OUT_PP)      || \
                                   ((MODE) == GPIO_MODE_AF_OD)  || ((MODE) == GPIO_MODE_AF_PP)       || \
                                   ((MODE) == OUTPUT)           || ((MODE) == INPUT))


//系统初始化函数
void Sys_Init(void);
//快速初始化GPIO
void GPIO_Pin_Config(uint32_t Pxx, uint8_t GPIO_MODE);
//单个GPIO电平翻转
void GPIO_ReversePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
//对 8 个 GPIO操作，不会影响同GPIO的其它IO输出
void  GPIO_Low8BitWrite(GPIO_TypeDef *GPIOx,uint8_t dat);
void GPIO_High8BitWrite(GPIO_TypeDef *GPIOx,uint8_t dat);



#endif /* __SYS_H */
