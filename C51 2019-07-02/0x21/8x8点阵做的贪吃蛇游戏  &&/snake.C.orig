//proteus仿真论坛:proteus.5d6d.com
#include <reg51.h>
#define uchar unsigned char
#define SNAKE 20                 //最大长度
#define TIME 50                 //显示延时时间
#define SPEED 71               //速度控制
//#define  keyenable 1
sbit keyenable=P3^6;			//方向使能
/*sbit keyx=P0^1;					//左右
sbit keyy=P0^2;					//上下	*/
//sbit up=P0^0;
sbit up=P3^3;       //down
sbit down=P3^1;
sbit right=P3^2;
sbit left=P3^4;
uchar x[SNAKE+1];
uchar y[SNAKE+1];          
uchar time,n,i,e;              //延时时间，当前蛇长，通用循环变量，当前速度		
char addx,addy;                //位移偏移量
/********************
延时程序
*********************/
void delay(char MS)
{
char us,usn;
while(MS!=0)
{
usn = 0;
while(usn!=0)
{
us=0xff;
while (us!=0){us--;};
usn--;
}
MS--;
}
}
/*******************************************
判断碰撞
*******************************************/
bit knock()
{bit k;
k=0;
if(x[1]>7||y[1]>7)k=1;                             //撞墙
for(i=2;i<n;i++)if((x[1]==x[i])&(y[1]==y[i]))k=1;  //撞自己
return k;
}
/*****************
上下左右键位处理
*****************/
void turnkey()// interrupt 0 using 2  
{//up=1;
if(keyenable)
{
if(left){addy=0;if(addx!=1)addx=-1; else addx=1;}
if(right){addy=0;if(addx!=-1)addx=1; else addx=-1;}
if(up){addx=0;if(addy!=-1)addy=1; else addy=-1;}
if(down){addx=0;if(addy!=1)addy=-1; else addy=1;}
/*if(keyy)
{addy=0;                                   //左右
if(keyx)if(addx==-1)addx=-1; else addx=1;  //左
else
if(addx==1)addx=1; else addx=-1;           //右
}
else
{addx=0;                                   //上下
if(keyx)if(addy==1)addy=1; else addy=-1;   //下
else
if(addy==-1)addy=-1; else addy=1;          //上	  
} */
}
}
/*****************
乘方程序
*****************/
uchar mux(uchar temp) 
{
if(temp==7)return 128;
if(temp==6)return 64;
if(temp==5)return 32;
if(temp==4)return 16;
if(temp==3)return 8;
if(temp==2)return 4;
if(temp==1)return 2;
if(temp==0)return 1;
return 0;
}
/*****************
显示时钟 显示程序
*****************/
void timer0(uchar k)
{while(k--)
{for(i=0;i<SNAKE+1;i++)
{P2=mux(x[i]);P1=255-mux(y[i]);
turnkey();                     //上下左右键位处理
delay(TIME);                   //显示延迟
P2=0x00;P1=0xff;
}}
} 
/*****************
主程序
*****************/	
void main(void)
{e=SPEED;
 P0=0x00;
 P1=0xff;
 P2=0x00;
 P3=0x00;
while(1)       
 {//if(keyenable==1){P1=0x00;P2=0xff;}else{P1=0xff;P2=0x00;}
 for(i=3;i<SNAKE+1;i++)x[i]=100;for(i=3;i<SNAKE+1;i++)y[i]=100;//初始化
 x[0]=4;y[0]=4;                                                //果子                            
 n=3;                                                          //蛇长 n=-1
 x[1]=1;y[1]=0;                                                //蛇头
 x[2]=0;y[2]=0;                                                //蛇尾1
 addx=0;addy=0;                                                //位移偏移
 //k=1;
 while(1){if(keyenable)break;timer0(1);}
 while(1)         
  {timer0(e);
   if(knock()){e=SPEED;break;}                          //判断碰撞
        if((x[0]==x[1]+addx)&(y[0]==y[1]+addy))         //是否吃东西
           {n++;
		   if(n==SNAKE+1)
		   {n=3;e=e-10;
		   for(i=3;i<SNAKE+1;i++)x[i]=100;
           for(i=3;i<SNAKE+1;i++)y[i]=100;
		   }
           x[0]=x[n-2];
           y[0]=y[n-2];
           }
    for(i=n-1;i>1;i--){x[i]=x[i-1];y[i]=y[i-1];}        
    //x[n-1]=x[2];y[n-1]=y[2];
    x[1]=x[2]+addx;y[1]=y[2]+addy;                     //移动
  }						
 }			
}