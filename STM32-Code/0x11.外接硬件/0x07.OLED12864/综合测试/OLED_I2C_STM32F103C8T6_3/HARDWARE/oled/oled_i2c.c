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

#if          0   // Ӳ��I2C
void I2Cx_Init(void)
{
	I2C_InitTypeDef  I2C_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure; 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	/*STM32F103C8T6оƬ��Ӳ��I2C: PB6 -- SCL; PB7 -- SDA */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;//I2C���뿪©���
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	I2C_DeInit(I2C1);//ʹ��I2C1
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x30;//������I2C��ַ,���д��
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 400000;//400K

	I2C_Cmd(I2C1, ENABLE);
	I2C_Init(I2C1, &I2C_InitStructure);
}

void I2C_WriteByte(uint8_t addr,uint8_t data)
{
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C1, ENABLE);//����I2C1
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,��ģʽ*/

	I2C_Send7bitAddress(I2C1, OLED_ADDR, I2C_Direction_Transmitter);//������ַ -- Ĭ��0x78
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C1, addr);//�Ĵ�����ַ
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C1, data);//��������
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C1, ENABLE);//�ر�I2C1����
}

void WriteCmd(unsigned char I2C_Command)//д����
{
	I2C_WriteByte(0x00, I2C_Command);
}

void WriteDat(unsigned char I2C_Data)//д����
{
	I2C_WriteByte(0x40, I2C_Data);
}
#else


void WriteCmd(unsigned char I2C_Command)//д����
{
	I2C_Start();
	I2C_Write_Byte(OLED_ADDR);//OLED������ַ
	I2C_Respons();
	I2C_Write_Byte(0x00);//д����
	I2C_Respons();
	I2C_Write_Byte(I2C_Command);
	I2C_Respons();
	I2C_Stop();
}

void WriteDat(unsigned char I2C_Data)//д����
{
	I2C_Start();
	I2C_Write_Byte(OLED_ADDR);
	I2C_Respons();
	I2C_Write_Byte(0x40);//д����
	I2C_Respons();
	I2C_Write_Byte(I2C_Data);
	I2C_Respons();
	I2C_Stop();
}
#endif

void OLED_Init(void)
{
	delay_ms(100); //�������ʱ����Ҫ
	
	WriteCmd(0XAE);  //display off //����ʾ
	WriteCmd(0X20); 	//Set Memory Addressing Mode	//�����ڴ�Ѱַģʽ//00��ˮƽѰַģʽ;  01����ֱѰַģʽ;   10��ҳ��Ѱַģʽ(����);    11����Ч
	WriteCmd(0X02); 	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0XB0); 	//Set Page Start Address for Page Addressing Mode,0-7    //Ϊҳ��Ѱַģʽ����ҳ�濪ʼ��ַ��0-7
	WriteCmd(0XC8); 	//Set COM Output Scan Direction    //  ���������ɨ�跽��C8����   C0���·��ã�
	WriteCmd(0X00);  //---set low column address   //���õ��е�ַ
	WriteCmd(0X10);  //---set high column address  //���ø��е�ַ
	WriteCmd(0X40);  //--set start line address
	WriteCmd(0X81);  //--set contrast control register
	WriteCmd(0XFF);  //���ȵ��� 0x00~0xff
	WriteCmd(0XA1);  //--set segment re-map 0 to 127//����ϸ����ӳ��
	WriteCmd(0XA6);  //--set normal display        //��������/����A6����  A7������ʾ ��
	WriteCmd(0XA8);  //--set multiplex ratio(1 to 64)  //���ö�·���ñ���
	WriteCmd(0X3F);  //
	WriteCmd(0XA4);  //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0XD3);  //-set display offset     //������ʾƫ��
	WriteCmd(0X00);  //-not offset
	WriteCmd(0XD5);  //--set display clock divide ratio/oscillator frequency  // ������ʾʱ�ӷ�Ƶ
	WriteCmd(0XF0);  //--set divide ratio
	WriteCmd(0XD9);  //--set pre-charge period  //����Ԥ�����
	WriteCmd(0X22);  //
	WriteCmd(0XDA);  //--set com pins hardware configuration  // ����COM����Ӳ������
	WriteCmd(0X12);  //���ñ���COM��������
	WriteCmd(0XDB);  //--set vcomh   //����  vcomh  ȡ��ѡ�񼶱�
	WriteCmd(0X20);  //0x20,0.77xVcc
	WriteCmd(0X8D);  //--set DC-DC enable
	WriteCmd(0X14);  //����ʾ�ڼ�ʹ�õ�ɱ�
	WriteCmd(0XAF);  //--turn on oled panel//����ʾ
	
	OLED_CLS(); // ��������
}

void OLED_SetPos(unsigned char x, unsigned char y) //������ʼ������
{ 
	WriteCmd(0xb0+y);  // ��ʼ ҳ�ĵ�ַ
	WriteCmd(((x&0xf0)>>4)|0x10); // ��ʼ�е�ַ�ĸ���λ
	WriteCmd(x&0x0f);    // ��ʼ��ַ�ĵ���λ
}

void OLED_Fill(unsigned char fill_Data)//ȫ�����
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

void OLED_CLS(void)//����
{
	OLED_Fill(0x00);
}

/*--------------------------------------------------------------
* Prototype      : void OLED_ON(void)
* Calls          : 
* Parameters     : none
* Description    : ��OLED�������л���
--------------------------------------------------------------*/
void OLED_ON(void)
{
	WriteCmd(0X8D);  //���õ�ɱ�
	WriteCmd(0X14);  //������ɱ�
	WriteCmd(0XAF);  //OLED����
}

//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          : 
// Parameters     : none
// Description    : ��OLED���� -- ����ģʽ��,OLED���Ĳ���10uA
//--------------------------------------------------------------
void OLED_OFF(void)
{
	WriteCmd(0X8D);  //���õ�ɱ�
	WriteCmd(0X10);  //�رյ�ɱ�
	WriteCmd(0XAE);  //OLED����
}

#if   ASCII_6X8_8x16_ENABLE

/*************************************************************
* ��ʾ ASCII �����Լ���ĸ

* x,y:��ʼ����  y----ҳ    x �ڼ���  

* ch[] Ϊһ���ַ���

* TextSize �ֺ� 1:6x8 2:8x16
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
					y = y + 3; //�������һ�е�����ַ� ������һ�м�����ʾ 
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
* ��ʾ16*32��Ӣ�ļ�����

* x,y:��ʼ����  y----ҳ    x �ڼ���  

* ch[] Ϊһ���ַ���
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
		for (i = 0; i < 4; i++) { //4��ʲô��˼��32���ַ��߶�Ϊ32���㣬����Ϊ8ҳ������8�У���ÿҳ8���㣬32/8=4
			OLED_SetPos(x, y + i);
			for(j = 0; j < 16; j++) { //16��ʲô����Ӣ���ַ��������ַ��Ŀ��
				WriteDat(F16x32[c][16 * i + j]);
			}
		}
		x = x + 16;
	}
}

#endif /* ASCII_16X32_ENABLE */


#if   ASCII_12x14_ENABLE

/*************************************************************
* ��ʾ12*24��Ӣ�ļ�����

* x,y:��ʼ����  y----ҳ    x �ڼ���  

* ch[] Ϊһ���ַ���
***************************************************************/
void OLED_Show12x24(uint8_t x,uint8_t y,uint8_t ch[])
{
	uint8_t i,j;
	uint8_t t,c;
	for(t = 0; ch[t] != '\0'; t++) {
		c = ch[t] - 32;
		if(x > 108) {
			x = 0;
			y = y + 3; //�������һ�е�����ַ� ������һ�м�����ʾ 
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
* ��ʾ116*16�ĺ���

* x,y:��ʼ����  y----ҳ    x �ڼ���  

* no Ϊ�����ַ��������� 
***************************************************************/
void OLED_ShowCN(u8 x,u8 y,u8 no)
{
  uint8_t t, i;
  for (i = 0; i < 2; i++)   //6��ʲô��˼��48���ַ��߶�Ϊ48���㣬OLED����Ϊ8ҳ������8�У���ÿҳ8���㣬����48/8=6
  {
    OLED_SetPos(x, y + i);
    for(t = 0; t < 16; t++)  //48��ʲô���ַ��Ŀ��Ϊ48���㡣
    {
      WriteDat(F16x16[no][16 * i + t]);
    }
  }
}

#endif /* CN_16X16_ENABLE */



#if   BMP_ENABLE

/*************************************************************
* ��ʾλͼ

* x0,y0 -- ��ʼ������(x0:0~127, y0:0~7); x1,y1 -- ���Խ���(������)������(x1:1~128,y1:1~8)

* BMP[] ��ʾBMPλͼ
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










