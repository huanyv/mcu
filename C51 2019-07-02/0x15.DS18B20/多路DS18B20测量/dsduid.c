#include<reg51.h>
#include<intrins.h>
#include <string.h>
#include <stdio.h>
#define uchar unsigned char
#define uint  unsigned int

sbit RS=  P2^0  ;							//液晶显示引脚定义
sbit RW=  P2^1  ;
sbit EN=  P2^2  ;
uint  t=0,dian=0;
uchar LCD_LINE_ONE[16]={"tp1:           "};		//定义显示屏幕
uchar LCD_LINE_TWO[16]={"tp2:           "};
//uchar LCD_LINE_THR[16]={"                "};

int Tm;
int  fushu=0 ;
sbit DQ= P3^3;										   
static unsigned char get_serial[]={		  //获取的八个DS18B20内部RAM64位序列号
   224, 0,0,0,  184,  197, 50, 40,
   215, 0,0,0,  184,  197, 51, 40
  //  82, 0,0,0,  184,  197, 52, 40
 // 101, 0,0,0,  184,  197,  53,40,
  //60, 0,0,0,  184,  197,  54,40,
   //11, 0,0,0,  184,  197,  55,40,
    //47, 0,0,0,  184,  197,  56,40,
	 //185, 0,0,0,  184,  197,  49,40,
 };
void delay( ms )					  //用于液晶显示的延时函数
{
	  int i ;
	  while(ms--)
	  {
	       for(i=0 ;i<5 ;i++ )  ;

	  }
}

uchar Read_LCD_State()				  //读取液晶显示的状态
{
 	uchar state;
	RS=0;RW=1;EN=1;delay(1);
	state=P0;
	EN = 0;delay(1);
	return state;
}
void LCD_Busy_Wait()				 //如果忙则等待函数
{
 	while((Read_LCD_State()&0x80)==0x80);
	delay(5);
}

void Write_LCD_Zhilin(uchar zl)			  //液晶显示写指令函数
{
	LCD_Busy_Wait();
	RS=0;RW=0;
	EN=0;
	P0=zl;
	EN=1;
	delay(1);
	EN=0;	
}
void Write_LCD_shuju(uchar date)	     //液晶显示写数据函数
{
 	LCD_Busy_Wait();
	RS=1;RW=0;
	EN=0;
	P0=date;
	EN=1;
	delay(1);
	EN=0;	
}
 void LCD_INIT()				//液晶显示初始化
{
    Write_LCD_Zhilin(0x38);	  // 显示模式设置
	delay(1);				  
	Write_LCD_Zhilin(0x01);	  // 显示清屏
	delay(1);				 
	Write_LCD_Zhilin(0x06);	  // 光标移动设置
	delay(1);
	Write_LCD_Zhilin(0x0c);	  // 开及光标设置
	delay(1);
}
 void Display_LCD_String(uchar p,uchar *s)		  //液晶显示写入函数
{
 	uchar i;
	Write_LCD_Zhilin(p|0x80)	;    //写地址高位为一
	//Write_LCD_Zhilin(0x40|0x80);
	for(i=0;i<16;i++)
	{
		Write_LCD_shuju(s[i]);
		delay(1); 	
	}
}
/***************************************************************************************/
void delays(int us)					   //用于DS18B20的延时函数
{ int s;
for ( s=0; s<us; s++);
}
void rst(void)						//DS18B20初始化
{
DQ = 1;
delays(2);
DQ = 0;
delays(30); //精确延时 480~960us
DQ = 1;
delays(8);
}
void write(unsigned char ku)		//DS18B20写函数
{
int i=0;
     for (i=0;i<8;i++)
    {
		DQ=0;
		DQ =ku&0x01;
		delays(3);
		DQ=1;
		ku>>=1;
    }
}
void match_rom(unsigned char *rom)	  //DS18B20匹配ROM函数
{
 unsigned char i;
 rst();							  //初始化
 write(0x55);					  //匹配ROM
 for(i=8;i>0;i--)
 {
    write(*(rom+i-1));
 }
}
unsigned int read(void)			  //DS18B20读函数，每次读16位
{
	int i=0;
	unsigned int u=0;
    for (i=0;i<16;i++)
    {
		DQ=0;
		u>>=1;
		DQ=1;
		if(DQ) u|=0x8000;
		delays(4);
     }
    return (u);
}
int  read0(unsigned char *seria)	//读取对应温度值并转换函数
{
  int temperature ;
  unsigned int tp;
  unsigned int lsb;
  rst();				//初始化
  write(0xCC);	//跳过RAM
	write(0x44);		//温度转换
	rst();				  //再次初始化
	write(0xCC); 
	match_rom(seria);    //匹配ROM函数调用
	 	write(0xBE);	 //读取存储器指令
	tp=read();			 //读取温度值
	if((tp&0xf800)==0xf800)		//判断正负数
	    {
		     fushu=1 ;
	  	    tp=~tp+1 ;
	    	lsb=(unsigned int)(tp*6.25); 
			dian=lsb%100;		  //取小数部分
		
	     	temperature=lsb/100;

		}
     else
	    {
		    fushu=0;
		    lsb=(unsigned int)(tp*6.25); 
			dian=lsb%100;  
		
	     	temperature=lsb/100;

    	 } 
     return(temperature);
}
/*****************************************************************************************/
void main()
{
      uint i ;
	  LCD_INIT();
	  EA=0 ;		 //使用DS18B20禁止任何中断
	  while(1)
	 {	  
	      for(i=0;i<2;i++)
		  {	
		      Tm=read0(get_serial+i*8);
				if(i==0)				   //判断是第几个的数据
				{
					   if(fushu==0)					   //判断是否加负号
					        sprintf(LCD_LINE_ONE+5," %d", Tm); 
					   if(fushu==1)
						    sprintf(LCD_LINE_ONE+5,"-%d", Tm); 
				       sprintf(LCD_LINE_ONE+10,".%d",dian);		//加入小数部分
					   Display_LCD_String(0x00,LCD_LINE_ONE);
				 }
				if(i==1)
				{  
				       if(fushu==0)	
					         sprintf(LCD_LINE_TWO+5," %d", Tm); 
					   if(fushu==1)
						     sprintf(LCD_LINE_TWO+5,"-%d", Tm); 
				       sprintf(LCD_LINE_TWO+10,".%d",dian);
					   Display_LCD_String(0x40,LCD_LINE_TWO); 
				}

		  }

		
	 }
}














