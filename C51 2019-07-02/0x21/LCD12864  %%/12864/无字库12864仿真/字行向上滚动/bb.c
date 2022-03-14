#include <reg51.h>
#define  uchar  unsigned char
#define  uint  unsigned int
#define LCDLCDDisp_Off   0x3e
#define LCDLCDDisp_On    0x3f
#define Page_Add     0xb8//ye
#define LCDCol_Add     0x40//lie
#define Start_Line     0xC0//hang
/*****液晶显示器的端口定义*****/
#define data_ora P0 /*液晶数据总线*/
sbit LCDMcs=P2^4 ;    /*片选1*/
sbit LCDScs=P2^3 ;    /*片选2*/
sbit LCDDi=P2^2 ;     /*数据/指令 选择*/
sbit LCDRW=P2^1 ;     /*读/写 选择*/
sbit LCDEnable=P2^0 ;     /*读/写 使能*/
uchar code hz1[]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*------------------------------------------------------------------------------
  源文件 / 文字 : 武
  宽×高（像素）: 16×16
  字模格式/大小 : 单色点阵液晶字模，纵向取模，字节倒序/32字节
  数据转换日期  : 2010-7-31 15:50:18
------------------------------------------------------------------------------*/
0x20,0x20,0x24,0x24,0x24,0xA4,0x24,0x24,0x20,0xFF,0x20,0x22,0x2C,0x20,0x20,0x00,
0x40,0xC0,0x7E,0x40,0x40,0x3F,0x22,0x22,0x20,0x03,0x0C,0x10,0x20,0x40,0xF8,0x00,
/*------------------------------------------------------------------------------
  源文件 / 文字 : 汉
  宽×高（像素）: 16×16
  字模格式/大小 : 单色点阵液晶字模，纵向取模，字节倒序/32字节
  数据转换日期  : 2010-7-31 15:51:45
------------------------------------------------------------------------------*/
0x10,0x60,0x02,0x0C,0xC0,0x02,0x1E,0xE2,0x02,0x02,0x02,0xE2,0x1E,0x00,0x00,0x00,
0x04,0x04,0x7C,0x03,0x80,0x80,0x40,0x20,0x13,0x0C,0x13,0x20,0x40,0x80,0x80,0x00,
/*------------------------------------------------------------------------------
  源文件 / 文字 : 理
  宽×高（像素）: 16×16
  字模格式/大小 : 单色点阵液晶字模，纵向取模，字节倒序/32字节
  数据转换日期  : 2010-7-31 15:52:29
------------------------------------------------------------------------------*/
0x04,0x84,0x84,0xFC,0x84,0x84,0x00,0xFE,0x92,0x92,0xFE,0x92,0x92,0xFE,0x00,0x00,
0x20,0x60,0x20,0x1F,0x10,0x10,0x40,0x44,0x44,0x44,0x7F,0x44,0x44,0x44,0x40,0x00,
/*------------------------------------------------------------------------------
  源文件 / 文字 : 工
  宽×高（像素）: 16×16
  字模格式/大小 : 单色点阵液晶字模，纵向取模，字节倒序/32字节
  数据转换日期  : 2010-7-31 15:53:19
------------------------------------------------------------------------------*/
0x00,0x04,0x04,0x04,0x04,0x04,0x04,0xFC,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,

/*------------------------------------------------------------------------------
  源文件 / 文字 : 大
  宽×高（像素）: 16×16
  字模格式/大小 : 单色点阵液晶字模，纵向取模，字节倒序/32字节
  数据转换日期  : 2010-7-31 15:53:53
------------------------------------------------------------------------------*/
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xFF,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,
0x80,0x80,0x40,0x20,0x10,0x0C,0x03,0x00,0x03,0x0C,0x10,0x20,0x40,0x80,0x80,0x00,

/*------------------------------------------------------------------------------
  源文件 / 文字 : 学
  宽×高（像素）: 16×16
  字模格式/大小 : 单色点阵液晶字模，纵向取模，字节倒序/32字节
  数据转换日期  : 2010-7-31 15:54:23
------------------------------------------------------------------------------*/
0x40,0x30,0x11,0x96,0x90,0x90,0x91,0x96,0x90,0x90,0x98,0x14,0x13,0x50,0x30,0x00,
0x04,0x04,0x04,0x04,0x04,0x44,0x84,0x7E,0x06,0x05,0x04,0x04,0x04,0x04,0x04,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
uchar code hz2[]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  信  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x80,0x60,0xF8,0x07,0x00,0x04,0x24,0x24,0x25,0x26,0x24,0x24,0x24,0x04,0x00,
0x01,0x00,0x00,0xFF,0x00,0x00,0x00,0xF9,0x49,0x49,0x49,0x49,0x49,0xF9,0x00,0x00,

/*--  文字:  息  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x00,0xFC,0x54,0x54,0x56,0x55,0x54,0x54,0x54,0xFC,0x00,0x00,0x00,0x00,
0x40,0x30,0x00,0x03,0x39,0x41,0x41,0x45,0x59,0x41,0x41,0x73,0x00,0x08,0x30,0x00,

/*--  文字:  工  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x04,0x04,0x04,0x04,0x04,0x04,0xFC,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,

/*--  文字:  程  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x24,0x24,0xA4,0xFE,0x23,0x22,0x00,0x3E,0x22,0x22,0x22,0x22,0x22,0x3E,0x00,0x00,
0x08,0x06,0x01,0xFF,0x01,0x06,0x40,0x49,0x49,0x49,0x7F,0x49,0x49,0x49,0x41,0x00,

/*--  文字:  学  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x30,0x11,0x96,0x90,0x90,0x91,0x96,0x90,0x90,0x98,0x14,0x13,0x50,0x30,0x00,
0x04,0x04,0x04,0x04,0x04,0x44,0x84,0x7E,0x06,0x05,0x04,0x04,0x04,0x04,0x04,0x00,

/*--  文字:  院  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0xFE,0x22,0x5A,0x86,0x10,0x0C,0x24,0x24,0x25,0x26,0x24,0x24,0x14,0x0C,0x00,
0x00,0xFF,0x04,0x08,0x07,0x80,0x41,0x31,0x0F,0x01,0x01,0x3F,0x41,0x41,0x71,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
uchar code hz3[]=
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*--  文字:  通  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x42,0xCC,0x00,0x00,0xE2,0x22,0x2A,0x2A,0xF2,0x2A,0x26,0x22,0xE0,0x00,0x00,
0x80,0x40,0x3F,0x40,0x80,0xFF,0x89,0x89,0x89,0xBF,0x89,0xA9,0xC9,0xBF,0x80,0x00,

/*--  文字:  信  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x80,0x60,0xF8,0x07,0x00,0x04,0x24,0x24,0x25,0x26,0x24,0x24,0x24,0x04,0x00,
0x01,0x00,0x00,0xFF,0x00,0x00,0x00,0xF9,0x49,0x49,0x49,0x49,0x49,0xF9,0x00,0x00,

/*--  文字:  工  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x04,0x04,0x04,0x04,0x04,0x04,0xFC,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,
0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,

/*--  文字:  程  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x24,0x24,0xA4,0xFE,0x23,0x22,0x00,0x3E,0x22,0x22,0x22,0x22,0x22,0x3E,0x00,0x00,
0x08,0x06,0x01,0xFF,0x01,0x06,0x40,0x49,0x49,0x49,0x7F,0x49,0x49,0x49,0x41,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
uchar code hz4[]=
{

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*--  文字:  许  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x40,0x42,0xCC,0x00,0x00,0x20,0x18,0x0F,0x08,0xF8,0x08,0x08,0x08,0x00,0x00,
0x00,0x00,0x00,0x7F,0x20,0x10,0x01,0x01,0x01,0x01,0xFF,0x01,0x01,0x01,0x01,0x00,

/*--  文字:  萍  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x44,0x84,0x14,0x64,0x0F,0x24,0xA4,0x24,0x24,0xE4,0x2F,0x24,0xA4,0x24,0x04,0x00,
0x08,0x09,0x78,0x04,0x03,0x04,0x04,0x05,0x04,0xFF,0x04,0x05,0x04,0x04,0x04,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00

};
/****************************************************************************
函数功能:LCD延时程序
入口参数:t
出口参数:
****************************************************************************/
void LCDdelay(uchar x)
{


   int d;
   uchar y;
   for(y=0;y<x;y++)
   for(d=0;d<10;d++);
}
/****************************************************************************
状态检查，LCD是否忙


*****************************************************************************/
void CheckState()		
{
   uchar dat,DATA;//状态信息（判断是否忙）
   LCDDi=0; // 数据\指令选择，D/I（RS）="L" ，表示 DB7∽DB0 为显示指令数据 
   LCDRW=1; //R/W="H" ，E="H"数据被读到DB7∽DB0 
   do
   {
      DATA=0x00;
      LCDEnable=1;	//EN下降源
	  LCDdelay(1);//延时
	  dat=DATA;
      LCDEnable=0;
      dat=0x80 & dat; //仅当第7位为0时才可操作(判别busy信号)
    }
    while(!(dat==0x00));
}
/*****************************************************************************
函数功能:写命令到LCD程序，RS(DI)=L,RW=L,EN=H，即来一个脉冲写一次
入口参数:cmdcode
出口参数:
*****************************************************************************/
void write_com(uchar cmdcode)
{
    CheckState();//检测LCD是否忙
	LCDDi=0;
	LCDRW=0;
	P1=cmdcode;		
	LCDdelay(1);
	LCDEnable=1;
	LCDdelay(1);
	LCDEnable=0;
}

/*****************************************************************************
函数功能:写数据到LCD程序，RS(DI)=H,RW=L,EN=H，即来一个脉冲写一次
入口参数:LCDDispdata
出口参数:
*****************************************************************************/
void write_data(uchar LCDDispdata)
{
    CheckState();//检测LCD是否忙
	LCDDi=1;
	LCDRW=0;
	P1=LCDDispdata;
	LCDdelay(1);
	LCDEnable=1;
	LCDdelay(1);
	LCDEnable=0;
}
/*****************************************************************************
/*****************************************************************************
函数功能:LCD初始化程序
入口参数:
出口参数:
*****************************************************************************/
void init_lcd()
{
	LCDdelay(1);	
	LCDMcs=1;//刚开始关闭两屏
	LCDScs=1;
	LCDdelay(1);
	write_com(LCDLCDDisp_Off);	 //写初始化命令
	write_com(Page_Add+0);
	write_com(Start_Line+0);
	write_com(LCDCol_Add+0);
	write_com(LCDLCDDisp_On);
}
/**************************************************************************
函数功能:清除LCD内存程序
入口参数:pag,col,hzk
出口参数:
*****************************************************************************/
void Clr_Scr()
{
	uchar j,k;
	LCDMcs=0; //左、右屏均开显示
	LCDScs=0;
 	write_com(Page_Add+0);
 	write_com(LCDCol_Add+0);
 	for(k=0;k<8;k++)//控制页数0-7，共8页
 	{
		write_com(Page_Add+k); //每页每页进行写
  		for(j=0;j<64;j++)  //每页最多可写32个中文文字或64个ASCII字符
		{
      		write_com(LCDCol_Add+j);
			write_data(0x00);//控制列数0-63，共64列，写点内容，列地址自动加1
		}
	}
}
/*****************************************************************************
函数功能:一行一行显示
入口参数:page,column,hzk
出口参数:
*****************************************************************************/
Disp(uchar page,uchar column, uchar code *word)
{
uchar i;
//左屏
LCDMcs=0; 
LCDScs=1;
//上半字
write_com(0xb8|page);
write_com(0x40|column);
for(i=0;i<16;i++)
write_data(word[i]);
for(i=32;i<48;i++)
write_data(word[i]);
for(i=64;i<80;i++)
write_data(word[i]);
for(i=96;i<112;i++)
write_data(word[i]);
//下半字
write_com(0xb8|page+1);
write_com(0x40|column);
for(i=16;i<32;i++)
write_data(word[i]);
for(i=48;i<64;i++)
write_data(word[i]);
for(i=80;i<96;i++)
write_data(word[i]);
for(i=112;i<128;i++)
write_data(word[i]);
//右屏
LCDMcs=1; 
LCDScs=0;
//上半字
write_com(0xb8|page);
write_com(0x40);
for(i=128;i<144;i++)
write_data(word[i]);
for(i=160;i<176;i++)
write_data(word[i]);
for(i=192;i<208;i++)
write_data(word[i]);
for(i=224;i<240;i++)
write_data(word[i]);
//下半字
write_com(0xb8|page+1);
write_com(0x40);
for(i=144;i<160;i++)
write_data(word[i]);
for(i=176;i<192;i++)
write_data(word[i]);
for(i=208;i<224;i++)
write_data(word[i]);
for(i=240;i<250;i++)
write_data(word[i]);
}

void main()
{ 
uint k=0;
	init_lcd();
	Clr_Scr();
     k=0;
      for(k=0xc0;k<0xff;k++)
	{
		 Disp(0,0,hz1);
		 Disp(2,0,hz2);
		 Disp(4,0,hz3);
		 Disp(6,0,hz4);
         LCDMcs=0; 
         LCDScs=0;
		 write_com(k);
		 LCDdelay(2);

	}
while(1)
    {
  
	}
}
