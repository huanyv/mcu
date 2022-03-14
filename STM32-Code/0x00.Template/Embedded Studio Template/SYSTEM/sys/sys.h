#ifndef _SYS_H_
#define _SYS_H_
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


//位定义
//  xxout  输入
//  xxin   输出
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



//   单个GPIO电平翻转
void GPIO_ReversePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);


//以下为对 8 个 GPIO操作 ，不会影响同GPIO的其它IO输出
void  GPIO_Low8BitWrite(GPIO_TypeDef *GPIOx,uint8_t dat);
void GPIO_High8BitWrite(GPIO_TypeDef *GPIOx,uint8_t dat);



#endif



