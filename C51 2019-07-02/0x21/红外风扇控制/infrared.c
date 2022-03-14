#include "infrared.h"
#include "timer.h"


extern uint speed;


uchar IrValue[6];
uchar Time;

bit FLAG = 0; // 手动自动切换标志位
bit FLAG1 = 0; // 启停标志位

void Intrared_SPEED_Ctrl(void)
{
	
	if(IrValue[2] == 0x07)
	{
		speed = 2;
		IrValue[2] = 0;
	}
	else if(IrValue[2] == 0x16)
	{
		speed = 5;
		IrValue[2] = 0;
	}
	else if(IrValue[2] == 0x0C)
	{
		speed = 10;
		IrValue[2] = 0;
	}
	

	

}

void Intrared_MODE_Ctrl(void)
{
	if(IrValue[2] == 0x47)  // 启
	{
		FLAG1 = 1;
		TR0 = 1;
		ET0 = 1;
		IrValue[2] = 0;
	}
	if(IrValue[2] == 0x40) // 停
	{
		FLAG1 = 0;
		TR0 = 0;
		ET0 = 0;
		motor = 1;		
		IrValue[2] = 0;
	}
	
	if(IrValue[2] == 0x19) // 手动 
	{
		FLAG = 0;
		IrValue[2] = 0;
	}
	if(IrValue[2] == 0x18) // 自动
	{
		FLAG = 1;		
		IrValue[2] = 0;
	}
	
}

void IrInit(void)
{
	IT0=1;//下降沿触发
	EX0=1;//打开中断0允许
	EA=1;	//打开总中断

	IRIN=1;//初始化端口
}

void ReadIr() interrupt 0
{
	uchar j,k;
	uint err;
	Time=0;					 
	delay(700);	//7ms
	if(IRIN==0)		//确认是否真的接收到正确的信号
	{	 
		
		err=1000;				//1000*10us=10ms,超过说明接收到错误的信号
		/*当两个条件都为真是循环，如果有一个条件为假的时候跳出循环，免得程序出错的时
		侯，程序死在这里*/	
		while((IRIN==0)&&(err>0))	//等待前面9ms的低电平过去  		
		{			
			delay(1);
			err--;
		} 
		if(IRIN==1)			//如果正确等到9ms低电平
		{
			err=500;
			while((IRIN==1)&&(err>0))		 //等待4.5ms的起始高电平过去
			{
				delay(1);
				err--;
			}
			for(k=0;k<4;k++)		//共有4组数据
	 		{				
				for(j=0;j<8;j++)	//接收一组数据
				{

					err=60;		
					while((IRIN==0)&&(err>0))//等待信号前面的560us低电平过去
					{
						delay(1);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0))	 //计算高电平的时间长度。
					{
						delay(10);	 //0.1ms
						Time++;
						err--;
						if(Time>30)
						{
							return;
						}
					}
					IrValue[k]>>=1;	 //k表示第几组数据
					if(Time>=8)			//如果高电平出现大于565us，那么是1
					{
						IrValue[k]|=0x80;
					}
					Time=0;		//用完时间要重新赋值							
				}
			}
		}
		if(IrValue[2]!=~IrValue[3])
		{
			return;
		}
	}			
}
