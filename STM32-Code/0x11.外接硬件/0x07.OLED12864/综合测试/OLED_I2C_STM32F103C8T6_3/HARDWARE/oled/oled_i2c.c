#include "oled_i2c.h"
#include "delay.h"
#include "i2c.h"

//User FONT Lib  #include ""
/******************BEGIN************************/

#if     ASCII_6X8_8x16_ENABLE
#include "ascii_6x8.h"
#include "ascii_8x16.h"
#endif

#if     ASCII_12x14_ENABLE
#include "ascii_12x24.h"
#endif

#if     ASCII_16X32_ENABLE
#include "ascii_16x32.h"
#endif

#if     CN_16X16_ENABLE
#include "cn_16x16.h"
#endif

#if     BMP_ENABLE
#include "bmp.h"
#endif  /* FONT Lib include */

/*******************END*************************/

#if          0   // 硬件I2C
void I2Cx_Init(void)
{
	I2C_InitTypeDef  I2C_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure; 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	/*STM32F103C8T6芯片的硬件I2C: PB6 -- SCL; PB7 -- SDA */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;//I2C必须开漏输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	I2C_DeInit(I2C1);//使用I2C1
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x30;//主机的I2C地址,随便写的
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 400000;//400K

	I2C_Cmd(I2C1, ENABLE);
	I2C_Init(I2C1, &I2C_InitStructure);
}

void I2C_WriteByte(uint8_t addr,uint8_t data)
{
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C1, ENABLE);//开启I2C1
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/

	I2C_Send7bitAddress(I2C1, OLED_ADDR, I2C_Direction_Transmitter);//器件地址 -- 默认0x78
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C1, addr);//寄存器地址
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C1, data);//发送数据
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C1, ENABLE);//关闭I2C1总线
}

void WriteCmd(unsigned char I2C_Command)//写命令
{
	I2C_WriteByte(0x00, I2C_Command);
}

void WriteDat(unsigned char I2C_Data)//写数据
{
	I2C_WriteByte(0x40, I2C_Data);
}
#else


void WriteCmd(unsigned char I2C_Command)//写命令
{
	I2C_Start();
	I2C_Write_Byte(OLED_ADDR);//OLED器件地址
	I2C_Respons();
	I2C_Write_Byte(0x00);//写命令
	I2C_Respons();
	I2C_Write_Byte(I2C_Command);
	I2C_Respons();
	I2C_Stop();
}

void WriteDat(unsigned char I2C_Data)//写数据
{
	I2C_Start();
	I2C_Write_Byte(OLED_ADDR);
	I2C_Respons();
	I2C_Write_Byte(0x40);//写数据
	I2C_Respons();
	I2C_Write_Byte(I2C_Data);
	I2C_Respons();
	I2C_Stop();
}
#endif

void OLED_Init(void)
{
	delay_ms(100); //这里的延时很重要
	
	WriteCmd(0XAE);  //display off //关显示
	WriteCmd(0X20); 	//Set Memory Addressing Mode	//设置内存寻址模式//00，水平寻址模式;  01，垂直寻址模式;   10，页面寻址模式(重置);    11，无效
	WriteCmd(0X02); 	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0XB0); 	//Set Page Start Address for Page Addressing Mode,0-7    //为页面寻址模式设置页面开始地址，0-7
	WriteCmd(0XC8); 	//Set COM Output Scan Direction    //  设置列输出扫描方向（C8正常   C0上下反置）
	WriteCmd(0X00);  //---set low column address   //设置低列地址
	WriteCmd(0X10);  //---set high column address  //设置高列地址
	WriteCmd(0X40);  //--set start line address
	WriteCmd(0X81);  //--set contrast control register
	WriteCmd(0XFF);  //亮度调节 0x00~0xff
	WriteCmd(0XA1);  //--set segment re-map 0 to 127//设置细分重映射
	WriteCmd(0XA6);  //--set normal display        //设置正常/反向（A6正常  A7反向显示 ）
	WriteCmd(0XA8);  //--set multiplex ratio(1 to 64)  //设置多路复用比率
	WriteCmd(0X3F);  //
	WriteCmd(0XA4);  //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0XD3);  //-set display offset     //设置显示偏移
	WriteCmd(0X00);  //-not offset
	WriteCmd(0XD5);  //--set display clock divide ratio/oscillator frequency  // 设置显示时钟分频
	WriteCmd(0XF0);  //--set divide ratio
	WriteCmd(0XD9);  //--set pre-charge period  //设置预充电期
	WriteCmd(0X22);  //
	WriteCmd(0XDA);  //--set com pins hardware configuration  // 设置COM引脚硬件配置
	WriteCmd(0X12);  //启用备用COM引脚配置
	WriteCmd(0XDB);  //--set vcomh   //设置  vcomh  取消选择级别
	WriteCmd(0X20);  //0x20,0.77xVcc
	WriteCmd(0X8D);  //--set DC-DC enable
	WriteCmd(0X14);  //在显示期间使用电荷泵
	WriteCmd(0XAF);  //--turn on oled panel//开显示
	
	OLED_CLS(); // 开机清屏
}

void OLED_SetPos(unsigned char x, unsigned char y) //设置起始点坐标
{ 
	WriteCmd(0xb0+y);  // 起始 页的地址
	WriteCmd(((x&0xf0)>>4)|0x10); // 起始列地址的高四位
	WriteCmd(x&0x0f);    // 起始地址的低四位
}

void OLED_Fill(unsigned char fill_Data)//全屏填充
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_SetPos(0,m);
		for(n=0;n<128;n++)
		{
			WriteDat(fill_Data);
		}
	}
}

void OLED_CLS(void)//清屏
{
	OLED_Fill(0x00);
}

/*--------------------------------------------------------------
* Prototype      : void OLED_ON(void)
* Calls          : 
* Parameters     : none
* Description    : 将OLED从休眠中唤醒
--------------------------------------------------------------*/
void OLED_ON(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X14);  //开启电荷泵
	WriteCmd(0XAF);  //OLED唤醒
}

//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          : 
// Parameters     : none
// Description    : 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
//--------------------------------------------------------------
void OLED_OFF(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X10);  //关闭电荷泵
	WriteCmd(0XAE);  //OLED休眠
}

#if   ASCII_6X8_8x16_ENABLE

/*************************************************************
* 显示 ASCII 数字以及字母

* x,y:起始坐标  y----页    x 第几列  

* ch[] 为一个字符串

* TextSize 字号 1:6x8 2:8x16
***************************************************************/
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0,t;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					WriteDat(F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			for(t = 0; ch[t] != '\0'; t++) {
				c = ch[t] - 32;
				if(x > 120) {
					x = 0;
					y = y + 3; //如果超过一行的最多字符 换到下一行继续显示 
				}
				for(i = 0; i < 2; i++) {
					OLED_SetPos(x,y + i);
					for(j = 0; j < 8; j++) {
						WriteDat(F8X16[c][8 * i + j]);
					}
				}
				x = x + 8;
			}
		}break;
	}
}
#endif /* ASCII_6X8_8x16_ENABLE */ 



#if   ASCII_16X32_ENABLE

/*************************************************************
* 显示16*32的英文及数字

* x,y:起始坐标  y----页    x 第几列  

* ch[] 为一个字符串
***************************************************************/
void OLED_Show16x32(uint8_t x,uint8_t y,uint8_t ch[])
{
  uint8_t i,j;
	uint8_t t,c;
	for(t = 0; ch[t] != '\0'; t++) {
		c = ch[t] - 32;
		if(x > 112) {
			x = 0;
			y = y+4;
		}
		for (i = 0; i < 4; i++) { //4是什么意思？32是字符高度为32个点，屏分为8页（就是8行），每页8个点，32/8=4
			OLED_SetPos(x, y + i);
			for(j = 0; j < 16; j++) { //16是什么？是英文字符和数字字符的宽度
				WriteDat(F16x32[c][16 * i + j]);
			}
		}
		x = x + 16;
	}
}

#endif /* ASCII_16X32_ENABLE */


#if   ASCII_12x14_ENABLE

/*************************************************************
* 显示12*24的英文及数字

* x,y:起始坐标  y----页    x 第几列  

* ch[] 为一个字符串
***************************************************************/
void OLED_Show12x24(uint8_t x,uint8_t y,uint8_t ch[])
{
	uint8_t i,j;
	uint8_t t,c;
	for(t = 0; ch[t] != '\0'; t++) {
		c = ch[t] - 32;
		if(x > 108) {
			x = 0;
			y = y + 3; //如果超过一行的最多字符 换到下一行继续显示 
		}
		for(i = 0; i < 3; i++) {
			OLED_SetPos(x,y + i);
			for(j = 0; j < 12; j++) {
				WriteDat(F12x24[c][12 * i + j]);
			}
		}
		x = x + 12;
	}
}

#endif  /* ASCII_12x14_ENABLE */



#if   CN_16X16_ENABLE
/*************************************************************
* 显示116*16的汉字

* x,y:起始坐标  y----页    x 第几列  

* no 为中文字符数组索引 
***************************************************************/
void OLED_ShowCN(u8 x,u8 y,u8 no)
{
  uint8_t t, i;
  for (i = 0; i < 2; i++)   //6是什么意思？48是字符高度为48个点，OLED屏分为8页（就是8行），每页8个点，所以48/8=6
  {
    OLED_SetPos(x, y + i);
    for(t = 0; t < 16; t++)  //48是什么？字符的宽度为48个点。
    {
      WriteDat(F16x16[no][16 * i + t]);
    }
  }
}

#endif /* CN_16X16_ENABLE */



#if   BMP_ENABLE

/*************************************************************
* 显示位图

* x0,y0 -- 起始点坐标(x0:0~127, y0:0~7); x1,y1 -- 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)

* BMP[] 显示BMP位图
***************************************************************/
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0)
		y = y1/8;
  else
		y = y1/8 + 1;
	
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
    for(x=x0;x<x1;x++)
		{
			WriteDat(BMP[j++]);
		}
	}
}

#endif /* BMP_ENABLE */










