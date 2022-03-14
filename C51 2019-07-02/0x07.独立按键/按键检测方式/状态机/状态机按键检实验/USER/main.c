#include<reg52.h>

typedef unsigned char uchar;
typedef unsigned int uint;

#define dula P0
#define PINC P3

//#define count 50000
//#define THx (65536-count)/256
//#define TLx (65536-count)%256

sbit A38=P2^2;
sbit B38=P2^3;
sbit C38=P2^4;

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;

uchar a=0,b=0,c=0,d=0;

uchar code distab[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d, 
						0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x40};
void delay(uint iii)
{
	while(iii--);
}
void display()
{
	uchar i;
	for(i=1;i<9;i++)
	{
		switch(i)
		{
			case 1:C38=0;B38=0;A38=0;
			dula=distab[d];break;
			case 2:C38=0;B38=0;A38=1;
			dula=distab[c];break;
			case 3:C38=0;B38=1;A38=0;
			dula=distab[b];break;
			case 4:C38=0;B38=1;A38=1;
			dula=distab[a];break;
			case 5:C38=1;B38=0;A38=0;break;
	
			
			case 6:C38=1;B38=0;A38=1;break;
						
			
			case 7:C38=1;B38=1;A38=0;break;

			case 8:C38=1;B38=1;A38=1;break;
						
		}
		delay(200);
		dula=0x00;
	}
}
uchar readkey(void)
{
	uchar keyval=0;  //////keyvai是最终键码，4个按键分别对应的键码是0x0e,0x0d,0x0b,0x07
	uchar newkey;      ////////newkey是当前键码，需要和上次键码比较
	static uchar keystate=0; ////状态值，起始为0，注意它是静态变量赋值后就保持到改写为止
	static uchar lastkey; /////lastkey记录上次检查时的键码，也是静态变量
	newkey=PINC&0X0F; /////键码就是PC口低4位取值每次都要读取
	switch(keystate)        //////按照状态值进行不同的处理，单片机启动后总是状态0，
	{
	case 0:                      /////状态0
		if(newkey!=0x0f)       //////如果有键
		{
			keystate=1;               //////有键记下状态1
			lastkey=newkey;        /////有键就用当前键码代替原来键码等待下次检查
		}
		break;                          //////如果无键直接跳出，有键进行上述处理后跳出，注意有键状态值已变
	case 1:                       ///////如上次有键，这次就转到状态1
		if(newkey==lastkey)   /////这次读取的键值如果和上次记录的一样，就是确认按键了
		{
			keyval=newkey;          /////取得键码
			keystate=2;                //////按键状态下次要转状态2
		}
		else                       //////如果读键和上次不同，不确认按键，除了不进行以上处理还要把状态值清0
			keystate=0;
		break;                   ///////跳出
	case 2:                 /////////状态2
		if(newkey==0x0f)   ///////如果10毫秒后仍然无键
			keystate=0;            //////下次回到状态0
		break;
	}
	return keyval;      ////////返回键码
}
void key()
{
	uchar kkk;
	kkk=readkey();
	if(kkk==0x0d)
	{
		a++;
		if(a==10)a=0;
	}
	if(kkk==0x0e)
	{
		b++;
		if(b==10)b=0;
	}
	if(kkk==0x0b)
	{
		c++;
		if(c==10)c=0;
	}
	if(kkk==0x07)
	{
		d++;
		if(a==10)d=0;
	}
}
void main()
{
	while(1)
	{
		display();
		key();
	}
}

//void timer0() interrupt 1
//{
//	static i=0;
//	TH0=THx;TL0=TLx;
//	if(++i==20)
//	{
//	
//	}
//}


















