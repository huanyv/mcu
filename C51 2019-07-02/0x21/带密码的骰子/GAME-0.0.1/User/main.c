#include "reg52.h"
#include "key.h"
#include <game.h>

sbit a38=P2^2;
sbit b38=P2^3;
sbit c38=P2^4;
sbit led = P2^0;

#define dula P0
//                   0    1    2    3    4    5    6    7    8    9    a    b    c    d    e    f    -    空
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x40,0x00}; 
uint mima[]={16,16,16,16};
uchar MEUN1 = 0;//键盘控制变量
bit MEUN2 = 0;//密码正确控制变量


void DisPlay_Init() {
	uchar i;
	for(i=0;i<8;i++) {
		switch(i) {
			case 0:c38 = 0;b38 = 0;a38 = 0;
					dula = table[mima[3]];break;//显示四个  '-'
			case 1:c38 = 0;b38 = 0;a38 = 1;
					dula = table[mima[2]];break;
			case 2:c38 = 0;b38 = 1;a38 = 0;
					dula = table[mima[1]];break;
			case 3:c38 = 0;b38 = 1;a38 = 1;
					dula = table[mima[0]];break;
			case 4:c38 = 1;b38 = 0;a38 = 0;
					dula = 0x00;break;
			case 5:c38 = 1;b38 = 0;a38 = 1;
					dula = 0x00;break;
			case 6:c38 = 1;b38 = 1;a38 = 0;
					dula = 0x00;break;
			case 7:c38 = 1;b38 = 1;a38 = 1;
					dula = 0x00;break;
		}
		delay(10);
		dula = 0x00;
	}
}
void Read_Key_Count() {
	static uchar i = 0,j = 0;
	uchar Key_Count = 0;
	Key_Count = Read_Key();
	if(Key_Count != 0) {//如果有按键按下
		MEUN1++;
		mima[MEUN1-1]=Key_Count-1;
		if(MEUN1==4) {
			MEUN1 = 0;
			
			if(mima[0] == 0&&mima[1] == 1&&mima[2] == 2&&mima[3] == 3) {//密码正确
				MEUN2 = 1;                                                //开启游戏模式
				for(i=0;i<4;i++) {//密码显示处  置位
					mima[i]=17;
				}
			}
			
			else {//密码错误
				for(i=0;i<4;i++) {
					
					for(j=0;j<200;j++) {
						DisPlay_Init();
					}															//显示 错误 跳动  有待完善
					delay(40000);
				}
				for(i=0;i<4;i++) {
					mima[i]=16;//显示 回归 四个   '-'
				}
			}
			
			
		}
		
	}
	
	
	
}
void main(void){
	while(1) {
		Read_Key_Count();
		DisPlay_Init();
		if(MEUN2 == 1){
			 game();
		}
			
		
	}
}
	