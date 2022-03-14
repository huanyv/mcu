#include "oled.h"
#include "i2c.h"



#if  ASCII_8x16_ENABLE
#include "ASCII_8x16.h"
#endif

#if  ASCII_16x32_ENABLE
#include "ASCII_16x32.h"
#endif




void delay_ms(uint16_t i) {
	uint8_t x;
	while(i--)
		for(x=0;x<123;x++);
}


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
	WriteCmd(0xb0+y);  // 起始页 地址
	WriteCmd(((x&0xf0)>>4)|0x10); // 起始列地址的高四位
	WriteCmd(x&0x0f);    // 起始地址的低四位
}

void OLED_Fill(uint8_t dat) {
	uint8_t i,j;
	for(i=0;i<8;i++) {
		OLED_SetPos(0,i);
		for(j=0;j<128;j++) {
			WriteDat(dat);
		}
	}
}

void OLED_CLS(void) {
	OLED_Fill(0x00);
}


#if  ASCII_8x16_ENABLE
void Showstr8x16(uint8_t x,uint8_t y,uint8_t ch[]) {
	uint8_t i,j,t;
	uint8_t c;
	for(t = 0;ch[t] != '\0';t++){
		c = ch[t] - 32;
		if(x>120)
			x = 0;
		for(i=0;i<2;i++) {
			OLED_SetPos(x,y+i);
			for(j=0;j<8;j++) {
				WriteDat(F8X16[c][8*i+j]);
			}
		}
		x = x+8;
		
	}	
}
#endif /* ASCII_8x16_ENABLE */

#if  ASCII_16x32_ENABLE
void Showstr16x32(uint8_t x,uint8_t y,uint8_t ch[]) {
	uint8_t i,j,t;
	uint8_t c;
	for(t = 0;ch[t] != '\0';t++){
		c = ch[t] - 32;
		if(x>112) {
			x = 0;
			y = y+4;
		}
		for(i=0;i<4;i++) {
			OLED_SetPos(x,y+i);
			for(j=0;j<16;j++) {
				WriteDat(F16x32[c][16*i+j]);
			}
		}
		x = x+16;
		
	}	
}
#endif /* ASCII_16x32_ENABLE */




















