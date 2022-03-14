#include "ds1302.h"
#include "delay.h"

uint8_t writedate[]={0x8c,0x88,0x86,0x84,0x82,0x80,0x8a};
uint8_t readdate[]={0x8d,0x89,0x87,0x85,0x83,0x81,0x8b};
  //             年   月   日   时   分   秒  星期
uint8_t time[]={0x18,0x12,0x15,0x20,0x44,0x00,0x06};
void GPIO_DS1302_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE); // 关闭 SWD
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = SCLK_PIN|IO_PIN|CE_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
void GPIO_DS1302_In(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin   = IO_PIN;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
void GPIO_DS1302_Out(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = IO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
uint8_t Read_DS1302(uint8_t addr) {
	uint8_t i,dat;
	CE = 0;
	delay_us(1);
	SCLK = 0;
	delay_us(1); // 预先把 时钟 拉低
	CE = 1;
	delay_us(1);
	GPIO_DS1302_Out();
	for(i=0;i<8;i++) {
		SCLK=0;
		delay_us(1);		
		
		IO=addr & 0x01;
		addr=addr>>1;
		
		SCLK=1;
		delay_us(1); // 上升沿写数据 
	}
	SCLK=0;
	delay_us(1); // 预先把 时钟 拉低
	GPIO_DS1302_In();
	for(i=0;i<8;i++) {
		SCLK=1;
		delay_us(1);
	
		dat = dat>>1;
		if(IO_in == 1)
			dat = dat | 0x80;
		
		SCLK=0;
		delay_us(1);  // 下降沿读数据 
	}
	CE=0;
	delay_us(1);
	SCLK=1;
	delay_us(1);
	GPIO_DS1302_Out();
	IO=0;
	delay_us(1);
	IO=1;
	delay_us(1);
	return dat;	
}
void Write_DS1302(uint8_t addr,uint8_t dat) {
	uint8_t i;
	CE=0;
	delay_us(1);
	SCLK=0;
	delay_us(1); // 预先把 时钟 拉低
	CE=1;
	delay_us(1);
	GPIO_DS1302_Out();
	for(i=0;i<8;i++) {
		SCLK=0;
		delay_us(1);		
		
		IO=addr & 0x01;
		addr=addr>>1;
		
		SCLK=1;
		delay_us(1); // 上升沿写数据 
	}
	SCLK=0;
	delay_us(1); // 预先把 时钟 拉低
	GPIO_DS1302_Out();
	for(i=0;i<8;i++)
	{
		SCLK=0;
		delay_us(1);
		
		IO=dat & 0x01;
		dat=dat>>1;
		
		SCLK=1;
		delay_us(1); // 上升沿写数据 
	}
	CE=0;
	delay_us(1);
}

void DS1302_Init(void)
{
	uint8_t i;
	Write_DS1302(0x8e,0x00); //关闭写保护
	for(i=0;i<7;i++)
	{
		Write_DS1302(writedate[i],time[i]);
	} 
	Write_DS1302(0x8e,0x80); // 打开写保护
}

void DS1302_ReadTime(void)
{
	uint8_t i;
	for(i=0;i<7;i++)
	{
		time[i]=Read_DS1302(readdate[i]);
		time[5] = (Read_DS1302(readdate[5])&0x7F); // 以防读出时间停止位 在读秒的寄存器中
	}
}


