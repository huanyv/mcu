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


void OLED_Init(void)
{
	delay_ms(100); //这里的延时很重要
	
	WriteCmd(0xAE);  //display off //关显示
	WriteCmd(0x20); 	//Set Memory Addressing Mode	//设置内存寻址模式//00，水平寻址模式;  01，垂直寻址模式;   10，页面寻址模式(重置);    11，无效
	WriteCmd(0x02); 	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xb0); 	//Set Page Start Address for Page Addressing Mode,0-7    //为页面寻址模式设置页面开始地址，0-7
	WriteCmd(0xc8); 	//Set COM Output Scan Direction    //  设置列输出扫描方向（C8正常   C0上下反置）
	WriteCmd(0x00);  //---set low column address   //设置低列地址
	WriteCmd(0x10);  //---set high column address  //设置高列地址
	WriteCmd(0x40);  //--set start line address
	WriteCmd(0x81);  //--set contrast control register
	WriteCmd(0xff);  //亮度调节 0x00~0xff
	WriteCmd(0xa1);  //--set segment re-map 0 to 127//设置细分重映射
	WriteCmd(0xa6);  //--set normal display        //设置正常/反向（A6正常  A7反向显示 ）
	WriteCmd(0xa8);  //--set multiplex ratio(1 to 64)  //设置多路复用比率
	WriteCmd(0x3F);  //
	WriteCmd(0xa4);  //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0xd3);  //-set display offset     //设置显示偏移
	WriteCmd(0x00);  //-not offset
	WriteCmd(0xd5);  //--set display clock divide ratio/oscillator frequency  // 设置显示时钟分频
	WriteCmd(0xf0);  //--set divide ratio
	WriteCmd(0xd9);  //--set pre-charge period  //设置预充电期
	WriteCmd(0x22);  //
	WriteCmd(0xda);  //--set com pins hardware configuration  // 设置COM引脚硬件配置
	WriteCmd(0x12);  //启用备用COM引脚配置
	WriteCmd(0xdb);  //--set vcomh   //设置  vcomh  取消选择级别
	WriteCmd(0x20);  //0x20,0.77xVcc
	WriteCmd(0x8d);  //--set DC-DC enable
	WriteCmd(0x14);  //在显示期间使用电荷泵
	WriteCmd(0xaf);  //--turn on oled panel//开显示
	
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
		WriteCmd(0xb0+m);		//page0-page1
		WriteCmd(0x00);		//low column start address
		WriteCmd(0x10);		//high column start address
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

//--------------------------------------------------------------
// Prototype      : void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); ch[] -- 要显示的字符串; TextSize -- 字符大小(1:6*8 ; 2:8*16)
// Description    : 显示codetab.h中的ASCII字符,有6*8和8*16可选择
//--------------------------------------------------------------
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
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
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}
#endif /* ASCII_6X8_8x16_ENABLE */ 



#if   ASCII_16X32_ENABLE

/*************************************************************
*显示16*32的英文及数字

*x,y:起始坐标  y----页    x 第几列  

* no数组中的字模 代号
***************************************************************/
//void OLED_Show16x32(uint8_t x,uint8_t y,uint8_t no)
//{
//  uint8_t t, i;
//	no = no - 32;
//  for (i = 0; i < 4; i++)  //6是什么意思？48是字符高度为48个点，屏分为8页（就是8行），每页8个点，48/8=6
//  {
//    OLED_SetPos(x, y + i);
//    for(t = 0; t < 16; t++) //24是什么？是英文字符和数字字符的宽度
//    {
//      WriteDat(F16x32[no][16 * i + t]);
//    }
//  }
//}

void OLED_Show16x32(uint8_t x,uint8_t y,uint8_t ch[])
{
	unsigned char c = 0,i = 0,j = 0;
	while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 112)
				{
					x = 0;
					y = y+4;
				}
				OLED_SetPos(x,y);
				for(i=0;i<16;i++)
					WriteDat(F16x32[c][i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<16;i++)
					WriteDat(F16x32[c][i+16]);
				OLED_SetPos(x,y+2);
				for(i=0;i<16;i++)
					WriteDat(F16x32[c][i+32]);
				OLED_SetPos(x,y+3);
				for(i=0;i<16;i++)
					WriteDat(F16x32[c][i+48]);
				x += 16;
				j++;
			}
}

#endif /* ASCII_16X32_ENABLE */


#if   ASCII_12x14_ENABLE

/*************************************************************
*显示12*24的英文及数字

*x,y:起始坐标  y----页    x 第几列  

* no数组中的字模 代号
***************************************************************/
//void OLED_Show12x24(uint8_t x,uint8_t y,uint8_t no)
//{
//  uint8_t t, i;
//	no = no - 32;
//  for (i = 0; i < 3; i++)  //6是什么意思？48是字符高度为48个点，屏分为8页（就是8行），每页8个点，48/8=6
//  {
//    OLED_SetPos(x, y + i);
//    for(t = 0; t < 12; t++) //24是什么？是英文字符和数字字符的宽度
//    {
//      WriteDat(F12x24[no][12 * i + t]);
//    }
//  }
//}

void OLED_Show12x24(uint8_t x,uint8_t y,uint8_t ch[])
{
	unsigned char c = 0,i = 0,j = 0;
	while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 116)
				{
					x = 0;
					y = y+3;
				}
				OLED_SetPos(x,y);
				for(i=0;i<12;i++)
					WriteDat(F12x24[c][i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<12;i++)
					WriteDat(F12x24[c][i+12]);
				OLED_SetPos(x,y+2);
				for(i=0;i<12;i++)
					WriteDat(F12x24[c][i+24]);
				OLED_SetPos(x,y+3);
				x += 12;
				j++;
			}
}

#endif  /* ASCII_12x14_ENABLE */



#if   CN_16X16_ENABLE
//--------------------------------------------------------------
// Prototype      : void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); N:汉字在codetab.h中的索引
// Description    : 显示codetab.h中的汉字,16*16点阵
//--------------------------------------------------------------
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
}
//与上效果一样 ， 但需要用 二维数组
//void OLED_ShowCN(u8 x,u8 y,u8 no)
//{                                 
//  u8 t, i;
//  for (i = 0; i < 2; i++)   //6是什么意思？48是字符高度为48个点，OLED屏分为8页（就是8行），每页8个点，所以48/8=6
//  {
//    OLED_SetPos(x, y + i);
//    for(t = 0; t < 16; t++)  //48是什么？字符的宽度为48个点。
//    {
//      WriteDat(F16x16[no][16 * i + t]);
//    }
//  }
//}

#endif /* CN_16X16_ENABLE */



#if   BMP_ENABLE

//--------------------------------------------------------------
// Prototype      : void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
// Calls          : 
// Parameters     : x0,y0 -- 起始点坐标(x0:0~127, y0:0~7); x1,y1 -- 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
// Description    : 显示BMP位图
//--------------------------------------------------------------
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










