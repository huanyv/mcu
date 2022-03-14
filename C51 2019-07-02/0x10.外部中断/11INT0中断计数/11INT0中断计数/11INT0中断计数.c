/*#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
sbit k1=P3^6;
uint	t0,a,b,c,d,i,j;
void init()
{
 	EA=1;
	IT0=1;
	EX0=1;
}
void delay(uchar z)
{
 	for(i=110;i>0;i--)
		for(j=z;j>0;j--);
}
void display(uint a,uint b,uint c,uint d)
{
	P2=0XFE;
	P1=table[a];
	delay(1);

	P2=0XFD;
	P1=table[b];
	delay(1);

	P2=0XFB;
	P1=table[c];
	delay(1);

	P2=0XF7;
	P1=table[d];
	delay(1);

}
void main()
{
	 init();
	 while(1)
	 {
	 	if(k1==0)
		{
			delay(10);
			if(k1==0)
			t0=0;
		}
		while(!k1);
		a=t0/1000;
		b=t0%1000/100;
		c=t0%100/10;
		d=t0%10;
		display(a,b,c,d);	
	 }
}
void exter0() interrupt 0
{
		t0++;
}*/
////////移位法；
#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
uchar vary[]={0,0,0,0};
sbit k1=P3^6;
uint	t0,a,b,c,d,i,j;
void init()
{
 	EA=1;
	IT0=1;
	EX0=1;
}
void delay(uchar z)
{
 	for(i=110;i>0;i--)
		for(j=z;j>0;j--);
}
void display()
{
	uint i1=0;
//	for(i=0;i<4;i++)
//	{
//	 	P2=~(1<<i);
//		P1=table[vary[i]];
//		delay(1);
//	}
	P2=0xfe;//点亮　最左边上
	for(i1=0;i1<4;i1++)
	{
		P1=table[vary[i1]];
		delay(2555);
		P1=0x00;//消隐
		P2=P2<<1|0x01;//往右移一个　　　|0x01 是移一个　同时灭掉前一个
	}
}
void main()
{
	 init();
	 while(1)
	 {
	 	if(k1==0)
		{
			delay(10);
			if(k1==0)
			t0=0;
		}
		while(!k1);	
		vary[0]=t0/1000;
		vary[1]=t0%1000/100;
		vary[2]=t0%100/10;
		vary[3]=t0%10;	
		display();
	 }
}
void exter0() interrupt 0
{
		t0++;
}


