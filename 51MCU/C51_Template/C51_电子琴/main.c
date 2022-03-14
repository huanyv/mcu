#include <REGX52.H>
#define     uint      unsigned int  
#define     uchar     unsigned char	 
	
#define     KEY       P3

sbit speaker = P1^4;                             //喇叭接口

uchar a,b;		                           //定义ab变量

void delay(uint i) // 1ms定时
{
	for(a = 0; a < i; a++)
		for(b = 0; b < 123; b++);
}

void check_key()                           //按键函数
{ 
	KEY=0xff;                		 //先赋给P2组口高电平
	if(KEY != 0xFF)   // 检测按键是否按下
	{
		delay(10);     // 消抖
		if(KEY != 0xFF)  // 再次检测按键是否按下
		{
			TR0 = 1;    // 打开定时器开关
			switch(KEY)      // 检测键值
			{
				case 0xfe:a = 0xfb; b = 0xe9; break;//根据不同按键ab的值不同
				case 0xfd:a = 0xfc; b = 0x5c; break;
				case 0xfb:a = 0xfc; b = 0xc1; break;
				case 0xf7:a = 0xfc; b = 0xef; break;
				case 0xef:a = 0xfd; b = 0x45; break;
				case 0xdf:a = 0xfd; b = 0x92; break;
				case 0xbf:a = 0xfd; b = 0xd0; break;
				case 0x7f:a = 0xfd; b = 0xee; break;
			}
		}
		while(KEY != 0xFF);   // 检测按键松手		
	} 
	else // 按键已松手
	{
		TR0 = 0; // 关闭定时器
		speaker=0; // 闲置蜂鸣器
	}
}
void main()
{
	TMOD=0x01;	     //定时器0工作方式1
	TH0=a;
	TL0=b;	          //赋初值
	EA = 1;          // 打开总开关
	ET0 = 1;           //打开定时器，但是未允许中断
	while(1)          //主循环
	{
		check_key();	    //扫描按键函数
	}
}
void time0() interrupt 1     //定时器0的工作函数
{
	TH0=a;
	TL0=b;				//将ab的值做为定时器的初值
	speaker=~speaker;	//喇叭电平取反喇叭根据不同的频率震动就可以发声了
}
