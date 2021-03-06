#include <reg51.h>
#define LCDLCDDisp_Off   0x3e
#define LCDLCDDisp_On    0x3f
#define Page_Add     0xb8//页地址
#define LCDCol_Add     0x40//列地址
#define Start_Line     0xC0//行地址
/*****液晶显示器的端口定义*****/
#define data_ora P0 /*液晶数据总线*/
sbit LCDMcs=P2^4 ;    /*片选1*/
sbit LCDScs=P2^3 ;    /*片选2*/
sbit LCDDi=P2^2 ;     /*数据/指令 选择*/
sbit LCDRW=P2^1 ;     /*读/写 选择*/
sbit LCDEnable=P2^0 ;     /*读/写 使能*/



unsigned char code Bmp1[]=
{
    /*------------------------------------------------------------------------------
      源文件 / 文字 : 来自剪贴板!武汉理工大学
      宽×高（像素）: 128×16
      字模格式/大小 : 单色点阵液晶字模，纵向取模，字节倒序/256字节
      数据转换日期  : 2010-7-29 17:52:57
      显示的汉字：武汉理工大学
    ------------------------------------------------------------------------------*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x20,0x20,0x24,0x24,0x24,0xE4,0x24,0x20,0x20,0xFE,0x20,0x24,0x28,0x20,
    0x00,0x20,0xC2,0x0C,0x80,0x60,0x04,0x7C,0x84,0x04,0x04,0xC4,0x3E,0x04,0x00,0x00,
    0x88,0x88,0xF8,0x88,0x88,0x00,0xFC,0x24,0x24,0xFC,0x24,0x24,0xFE,0x04,0x00,0x00,
    0x08,0x08,0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x08,0x0C,0x08,0x00,0x00,0x20,0x20,
    0x20,0x20,0x20,0x20,0xFE,0x20,0x20,0x20,0x20,0x20,0x30,0x20,0x00,0x40,0x30,0x10,
    0x52,0x5C,0x50,0x52,0x5C,0x50,0xD8,0x56,0x10,0x50,0x30,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x20,0x60,0x3F,0x20,0x20,0x1F,0x12,0x12,0x10,0x07,0x18,0x20,0x40,0x78,
    0x00,0x04,0x04,0x7E,0x41,0x40,0x20,0x10,0x0B,0x04,0x0B,0x10,0x20,0x60,0x20,0x00,
    0x10,0x30,0x1F,0x08,0x48,0x40,0x4B,0x49,0x49,0x7F,0x49,0x49,0x6B,0x40,0x08,0x20,
    0x20,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x30,0x20,0x00,0x40,0x40,
    0x20,0x10,0x08,0x06,0x01,0x02,0x04,0x08,0x10,0x20,0x60,0x20,0x00,0x04,0x04,0x04,
    0x04,0x04,0x24,0x44,0x3F,0x05,0x04,0x04,0x04,0x06,0x04,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
unsigned char code Bmp2[]=
{
    /*------------------------------------------------------------------------------
      源文件 / 文字 : 信息工程学院
      宽×高（像素）: 128×16
      字模格式/大小 : 单色点阵液晶字模，纵向取模，字节倒序/256字节
      数据转换日期  : 2010-7-29 18:34:04
      显示的汉字：信息工程学院
    ------------------------------------------------------------------------------*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x80,0x40,0xF0,0x0E,0x00,0x28,0x28,0x28,0x2A,0x2C,0x28,0x28,0x28,0x08,0x00,
    0x00,0x00,0x00,0xF8,0xA8,0xAC,0xAA,0xA8,0xA8,0xA8,0xFC,0x08,0x00,0x00,0x00,0x00,
    0x08,0x08,0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x08,0x0C,0x08,0x00,0x00,0x20,0x24,
    0xA4,0xFC,0x26,0x24,0x00,0x7C,0x24,0x24,0x24,0x24,0x7C,0x00,0x00,0x40,0x30,0x10,
    0x52,0x5C,0x50,0x52,0x5C,0x50,0xD8,0x56,0x10,0x50,0x30,0x00,0x00,0xFC,0x04,0x64,
    0x9C,0x20,0x58,0x48,0x4A,0x4C,0x48,0x48,0x18,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x7F,0x00,0x00,0x01,0x7D,0x25,0x25,0x25,0x25,0x7D,0x01,0x00,0x00,
    0x00,0x20,0x18,0x03,0x3A,0x42,0x46,0x5A,0x42,0x42,0x73,0x00,0x08,0x30,0x00,0x20,
    0x20,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x30,0x20,0x00,0x08,0x06,
    0x01,0x7F,0x01,0x42,0x49,0x49,0x49,0x7F,0x49,0x49,0x49,0x41,0x00,0x04,0x04,0x04,
    0x04,0x04,0x24,0x44,0x3F,0x05,0x04,0x04,0x04,0x06,0x04,0x00,0x00,0x7F,0x04,0x08,
    0x47,0x41,0x21,0x1F,0x01,0x01,0x3F,0x41,0x41,0x79,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
unsigned char code Bmp3[]=
{
    /*------------------------------------------------------------------------------
      源文件 / 文字 : 通信工程
      宽×高（像素）: 128×
      字模格式/大小 : 单色点阵液晶字模，纵向取模，字节倒序/256字节
      数据转换日期  : 2010-7-29 18:36:04
      显示汉字：通信工程
    ------------------------------------------------------------------------------*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x42,
    0xCC,0x00,0x00,0xF4,0x54,0x5C,0xF4,0x5C,0x56,0xF4,0x00,0x00,0x00,0x80,0x40,0xF0,
    0x0E,0x00,0x28,0x28,0x28,0x2A,0x2C,0x28,0x28,0x28,0x08,0x00,0x00,0x08,0x08,0x08,
    0x08,0x08,0xF8,0x08,0x08,0x08,0x08,0x0C,0x08,0x00,0x00,0x20,0x24,0xA4,0xFC,0x26,
    0x24,0x00,0x7C,0x24,0x24,0x24,0x24,0x7C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x10,
    0x0F,0x10,0x20,0x5F,0x42,0x42,0x5F,0x42,0x52,0x5F,0x40,0x40,0x00,0x00,0x00,0x7F,
    0x00,0x00,0x01,0x7D,0x25,0x25,0x25,0x25,0x7D,0x01,0x00,0x00,0x20,0x20,0x20,0x20,
    0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x30,0x20,0x00,0x08,0x06,0x01,0x7F,0x01,
    0x42,0x49,0x49,0x49,0x7F,0x49,0x49,0x49,0x41,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
unsigned char code Bmp4[]=
{
    /*------------------------------------------------------------------------------
      源文件 / 文字 : 0606班
      宽×高（像素）: 128×16
      字模格式/大小 : 单色点阵液晶字模，纵向取模，字节倒序/256字节
      数据转换日期  : 2010-7-29 18:37:59
      显示的汉字：0606班
    ------------------------------------------------------------------------------*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x20,0x10,0x10,0x20,0xC0,0x00,0x00,0xC0,
    0x20,0x10,0x10,0x30,0x00,0x00,0x00,0xC0,0x20,0x10,0x10,0x20,0xC0,0x00,0x00,0xC0,
    0x20,0x10,0x10,0x30,0x00,0x00,0x44,0x44,0xFC,0x44,0x04,0xC0,0x00,0xFE,0x84,0x84,
    0xFC,0x84,0x84,0x84,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,0x00,0x1F,
    0x22,0x21,0x21,0x21,0x1E,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,0x00,0x1F,
    0x22,0x21,0x21,0x21,0x1E,0x00,0x10,0x10,0x0F,0x48,0x28,0x11,0x08,0x27,0x20,0x20,
    0x3F,0x20,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
/****************************************************************************
函数功能:LCD延时程序
入口参数:t
出口参数:
****************************************************************************/
void LCDdelay(unsigned int t)
{
    unsigned int i,j;
    for(i=0; i<t; i++);
    for(j=0; j<10; j++);
}
/****************************************************************************
状态检查，LCD是否忙


*****************************************************************************/
void CheckState()
{
    unsigned char dat,DATA;//状态信息（判断是否忙）
    LCDDi=0; // 数据\指令选择，D/I（RS）="L" ，表示 DB7∽DB0 为显示指令数据
    LCDRW=1; //R/W="H" ，E="H"数据被读到DB7∽DB0
    do
    {
        DATA=0x00;
        LCDEnable=1;	//EN下降源
        LCDdelay(2);//延时
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
void write_com(unsigned char cmdcode)
{
    CheckState();//检测LCD是否忙
    LCDDi=0;
    LCDRW=0;
    P1=cmdcode;
    LCDdelay(2);
    LCDEnable=1;
    LCDdelay(2);
    LCDEnable=0;
}
/*****************************************************************************
函数功能:LCD初始化程序
入口参数:
出口参数:
*****************************************************************************/
void init_lcd()
{
    LCDdelay(100);
    LCDMcs=1;//刚开始关闭两屏
    LCDScs=1;
    LCDdelay(100);
    write_com(LCDLCDDisp_Off);	 //写初始化命令
    write_com(Page_Add+0);
    write_com(Start_Line+0);
    write_com(LCDCol_Add+0);
    write_com(LCDLCDDisp_On);
}
/*****************************************************************************
函数功能:写数据到LCD程序，RS(DI)=H,RW=L,EN=H，即来一个脉冲写一次
入口参数:LCDDispdata
出口参数:
*****************************************************************************/
void write_data(unsigned char LCDDispdata)
{
    CheckState();//检测LCD是否忙
    LCDDi=1;
    LCDRW=0;
    P1=LCDDispdata;
    LCDdelay(2);
    LCDEnable=1;
    LCDdelay(2);
    LCDEnable=0;
}
/*****************************************************************************
函数功能:清除LCD内存程序
入口参数:pag,col,hzk
出口参数:
*****************************************************************************/
void Clr_Scr()
{
    unsigned char j,k;
    LCDMcs=0; //左、右屏均开显示
    LCDScs=0;
    write_com(Page_Add+0);
    write_com(LCDCol_Add+0);
    for(k=0; k<8; k++) //控制页数0-7，共8页
    {
        write_com(Page_Add+k); //每页每页进行写
        for(j=0; j<64; j++) //每页最多可写32个中文文字或64个ASCII字符
        {
            write_com(LCDCol_Add+j);
            write_data(0x00);//控制列数0-63，共64列，写点内容，列地址自动加1
        }
    }
}
/*****************************************************************************
函数功能:左屏位置显示
入口参数:page,column,hzk
出口参数:
*****************************************************************************/
void Bmp_Left_Disp(unsigned char page,unsigned char column, unsigned char code *Bmp)
{
    unsigned char j=0,i=0;
    for(j=0; j<2; j++)
    {
        write_com(Page_Add+page+j);
        write_com(LCDCol_Add+column);
        for(i=0; i<64; i++)
            write_data(Bmp[128*j+i]);
    }
}
/*****************************************************************************
函数功能:右屏位置显示
入口参数:page,column,hzk
出口参数:
*****************************************************************************/
void Bmp_Right_Disp(unsigned char page,unsigned char column, unsigned char code *Bmp)
{
    unsigned char j=0,i=0;
    for(j=0; j<2; j++)
    {
        write_com(Page_Add+page+j);
        write_com(LCDCol_Add+column);
        for(i=64; i<128; i++)
            write_data(Bmp[128*j+i]);
    }
}


void main()
{
    init_lcd();
    Clr_Scr();
    LCDMcs=0; //左屏开显示
    LCDScs=1;
    Bmp_Left_Disp(0,0,Bmp1);// Bmp1为某个汉字的首地址
    Bmp_Left_Disp(2,0,Bmp2);
    Bmp_Left_Disp(4,0,Bmp3);
    Bmp_Left_Disp(6,0,Bmp4);
    LCDMcs=1; //右屏开显示
    LCDScs=0;
    Bmp_Right_Disp(0,0,Bmp1);
    Bmp_Right_Disp(2,0,Bmp2);
    Bmp_Right_Disp(4,0,Bmp3);
    Bmp_Right_Disp(6,0,Bmp4);
    while(1)
    {

    }
}