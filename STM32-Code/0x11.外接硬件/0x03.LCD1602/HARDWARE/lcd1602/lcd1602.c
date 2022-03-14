#include "lcd1602.h"
#include "delay.h"

void LCD_GPIO_Init() {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}

void Read_Busy() {
	GPIO_InitTypeDef GPIO_InitStructure;
	uint8_t dat,i = 0;
	LCD_RS = 0;
	LCD_RW = 1;
	delay_us(1);
	LCD_EN = 1;
	delay_ms(1);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;//读取数据前转为浮空输入
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	dat = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15);
	LCD_EN = 0;
	while((dat==1)&&i<255){						//避免死等
		i++;
	}
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;//换回推挽输出
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}
void LCD_Write_Cmd(uint8_t cmd) {
	Read_Busy();
	LCD_RS = 0;
	LCD_RW = 0;
	delay_us(2);
	GPIO_High8BitWrite(GPIOB,cmd);
	LCD_EN = 1;
	delay_us(2);
	LCD_EN = 0;
	delay_ms(5);
}
void LCD_Write_Dat(uint8_t dat) {
	Read_Busy();
	LCD_RS = 1;
	LCD_RW = 0;
	delay_us(2);
	GPIO_High8BitWrite(GPIOB,dat);
	LCD_EN = 1;
	delay_us(2);
	LCD_EN = 0;
	delay_ms(5);
}
void LCD_X_Y(uint8_t x,uint8_t y,uint8_t dat) {
	uint8_t adrr;
	if(x==1)
		adrr = 0x80;
	else
		adrr = 0xc0;
	LCD_Write_Cmd(adrr+y-1);
	LCD_Write_Dat(dat);
}
void LCD_Init(void) {
	LCD_GPIO_Init();
	LCD_Write_Cmd(0x38);
	delay_ms(10);
	LCD_Write_Cmd(0x38);
	LCD_Write_Cmd(0x0c);
	LCD_Write_Cmd(0x06);
	LCD_Write_Cmd(0x01);
}
void zidingyi(uint8_t (*s)[8],uint8_t len,uint8_t count)//自定义显示  字符   
{											//*s为自定义字符 的数组   len每个字符的数组 的长度   count：要自定义的个数
	uint8_t i,j;								
	for(j=1;j<=count;j++)
	{
		if(j==1)
			LCD_Write_Cmd(0x40);
		if(j==2)
			LCD_Write_Cmd(0x48);
		if(j==3)
			LCD_Write_Cmd(0x50);
		if(j==4)
			LCD_Write_Cmd(0x58);
		if(j==5)
			LCD_Write_Cmd(0x60);
		if(j==6)
			LCD_Write_Cmd(0x68);
		if(j==7)
			LCD_Write_Cmd(0x70);
		if(j==8)
			LCD_Write_Cmd(0x78);
		for(i=0;i<len;i++)
		{
			LCD_Write_Dat(s[j-1][i]);
		}
	}
}





