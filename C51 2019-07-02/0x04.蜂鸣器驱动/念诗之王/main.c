//142857.143
#include <reg52.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int

/*#define T1H 0xFE // 越大越快快快
#define T1L 0xE9 // 越大越快快
#define T1M 1000 // 越小越快*/

#define T1H 0xED
#define T1L 0x54
#define T1M 30  //原60   速度
	
#define OFFSET 11  // 1=Eb  http://tieba.baidu.com/p/5970194607    原   3    音调

#define L1 2
#define L2 4
#define L3 6
#define L5 9
#define L6 11
#define L7 13
#define M1 14
#define M2 16
#define M3 18
#define M4 19
#define M5 21
#define M6 23
#define H1 26
#define H2 28

#define l31 play(L3, 1, 0)
#define l51 play(L5, 1, 0)
#define l61 play(L6, 1, 0)
#define l71 play(L7, 1, 0)
#define m11 play(M1, 1, 0)
#define m21 play(M2, 1, 0)
#define m31 play(M3, 1, 0)
#define m61 play(M6, 1, 0)

#define l22 play(L2, 2, 0)
#define l32 play(L3, 2, 0)
#define l52 play(L5, 2, 0)
#define l62 play(L6, 2, 0)
#define l72 play(L7, 2, 0)
#define m12 play(M1, 2, 0)
#define m22 play(M2, 2, 0)
#define m32 play(M3, 2, 0)
#define m42 play(M4, 2, 0)
#define m52 play(M5, 2, 0)

#define l54 play(L5, 4, 0)
#define l64 play(L6, 4, 0)
#define l74 play(L7, 4, 0)
#define m14 play(M1, 4, 0)
#define m24 play(M2, 4, 0)
#define m34 play(M3, 4, 0)
#define m44 play(M4, 4, 0)
#define m54 play(M5, 4, 0)

sbit fmq = P1^5;			//蜂鸣器连接引脚

unsigned char code FRE_TH[] = {//定时器0高八位频率设定
0x0F,0xDF,0xE1,0xE3,0xE4,0xE6,0xE7,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
//低八度0,b1,1,#1,2,#2,3,4,#4,5,#5,6,#6,7
0xF0,0xF1,0xF2,0xF3,0xF3,0xF4,0xF5,0xF5,0xF6,0xF6,0xF7,0xF7,
//中音1,#1,2,#2,3,4,#4,5,#5,6,#6,7
0xF8,0xF8,0xF9,0xF9,0xF9,0xFA,0xFA,0xFA,0xFB,0xFB,0xFB,0xFB,0xFC
//高八度1,#1,2,#2,3,4,#4,5,#5,6,#6,7,#7
};
unsigned char code FRE_TL[] = {//定时器0低八位频率设定
0xFF,0x9C,0x76,0x38,0xC9,0x5B,0xC1,0x13,0x6F,0x97,0xC4,0xD0,0xDE,0xCD,
//低八度0,b1,1,#1,2,#2,3,4,#4,5,#5,6,#6,7
0xB3,0x95,0x5E,0x28,0xDB,0x89,0x33,0xCB,0x61,0xE8,0x6E,0xE6,
//中音1,#1,2,#2,3,4,#4,5,#5,6,#6,7
0x5B,0xCC,0x30,0x95,0xEE,0x45,0x9A,0xE5,0x30,0x73,0xB4,0xEE,0x2A
//高八度1,#1,2,#2,3,4,#4,5,#5,6,#6,7,#7
};

uchar t1m = T1M;
uchar musicOne;
uchar rapa; //起点音调
uchar rapb; //要升多少
uchar rapc; //现在是多少
bit rapn;
bit rapMode = 0;

uint timerFlag = 0;
bit timer = 1;

void delay(uchar beat) {
	while (beat--) {
		while (timer);
		timer = 1;
	}
}

void play(uchar music, uchar blen, uchar wlen) { // 播放音调 声音长度 静音长度
	rapMode = 0;
	musicOne = music;
	TH0 = FRE_TH[musicOne + OFFSET];
  TL0 = FRE_TL[musicOne + OFFSET];
	TR0 = 1;
	delay(blen);
	TR0 = 0;
	delay(wlen);
}

void rap(uchar start, char offset, uchar blen, uchar wlen) { //起始音调 音调偏移 声音长度 静音长度
	rapMode = 1;
	rapa = 0xF4 + start;
	if (offset < 0) {
		rapb = -offset;
		rapn = 1;
	} else {
		rapb = offset;
		rapn = 0;
	}
	rapc = rapa;
	TH0 = rapc;
	TL0 = 0xFF;
	TR0 = 1;
	t1m = T1M * blen - 20;
	while(timer);
	timer = 1;
	TR0 = 0;
	t1m = 19;
	while(timer);
	timer = 1;
	t1m = T1M;
	delay(wlen);
}

void main() {
	TMOD |= 0x11;
	EA=1;
	ET0 = 1;
	ET1 = 1;
	TH1 = T1H;
	TL1 = T1L;
	TR1 = 1;
	
	rap(1, 8, 1, 1);//人
	rap(6, -6, 1, 0);//是
	rap(5, 0, 1, 0);//衣
	rap(3, -2, 1, 0);//马
	rap(0, 0, 1, 0);//是
	rap(4, 0, 1, 1);//鞍
	rap(3, 5, 1, 0);//一
	rap(9, -7, 1, 0);//看
	rap(3, -1, 1, 0);//长
	rap(1, 0, 1, 0);//相
	rap(7, -5, 1, 0);//二
	rap(3, -2, 1, 0);//看
	rap(4, 0, 1, 1);//穿
	rap(3, 2, 1, 0);//白
	rap(4, 0, 1, 0);//天
	rap(2, -2, 1, 1);//想
	rap(7, -6, 1, 0);//夜
	rap(4, -4, 1, 0);//里
	rap(3, 0, 1, 1);//哭
	rap(9, -9, 1, 0);//做
	rap(9, -9, 1, 0);//梦
	rap(5, 0, 1, 0);//都
	rap(3, -2, 1, 0);//想
	rap(9, -9, 1, 0);//去
	rap(1, 0, 1, 0);//首
	rap(4, 0, 1, 1);//都
	rap(2, 7, 1, 1);//俩
	rap(5, -4, 1, 1);//脚
	rap(3, 7, 1, 0);//离
	rap(9, -5, 1, 0);//地
	rap(0, 0, 1, 1);//了
	rap(7, -5, 1, 0);//病
	rap(1, 5, 1, 0);//毒
	rap(7, -5, 1, 0);//就
	rap(5, 0, 1, 0);//关
	rap(9, -8, 1, 1);//闭
	rap(0, 0, 1, 1);//了
	rap(2, 6, 1, 0);//啥
	rap(5, -1, 1, 0);//都
	rap(7, -4, 1, 0);//上
	rap(2, 6, 1, 0);//不
	rap(9, -8, 1, 1);//去
	rap(0, 0, 1, 1);//了
	rap(0, 9, 2, 2);//嚎
	
	play(M6, 4, 0);//嗷
	
	l62; // 改革春风吹满地
	m32;
	m32;
	m22;
	m34;
	l54;
	m12;
	play(L6, 2, 2);
	
	rap(5, 0, 1, 0);//春
	rap(5, 0, 1, 0);//风
	rap(6, 0, 2, 0);//吹
	rap(4, -1, 2, 0);//满
	rap(9, -9, 2, 2);//地
	
	m32; // 中国人民真争气
	l62;
	m12;
	m12;
	m34;
	m12;
	m12;
	play(L6, 4, 2);
	
	rap(3, 3, 1, 0);//人
	rap(3, 3, 1, 0);//民
	rap(5, 0, 1, 1);//真
	rap(4, 0, 1, 1);//争
	rap(9, -9, 2, 2);//气
	
	play(M3, 1, 0); // 这个世界太疯狂
	play(M3, 1, 0);
	m32;
	m32;
	m52;
	m32;
	l62;
	m12;
	
	play(M5, 1, 0); // 耗子都给猫当伴娘
	play(M3, 1, 0);
	m32;
	m32;
	play(M3, 1, 0);
	play(M3, 1, 0);
	m32;
	play(M2, 1, 0);
	play(M1, 1, 0);
	l62;
	m12;
	
	play(H1, 2, 0); //齐得龙
	play(H1, 2, 0);
	play(H1, 2, 2);
	//m12; // 齐东强
	//m32;
	//play(L6, 2, 6);
	
	rap(2, 3, 2, 0);//齐东强
	rap(6, 0, 2, 0);
	rap(0, 9, 2, 6);
	
	play(H1, 2, 0); // 齐得龙东强
	play(H2, 2, 0);
	play(H1, 1, 0);
	play(H1, 2, 0);
	play(H1, 1, 0);
	play(H1, 2, 0);
	play(H2, 1, 0);
	play(H1, 1, 0);
	play(M6, 2, 2);
	
	l51;l31;l51;l51; // 记得那是2003年的第一场雪
	l51;l31;l51;l51;
	l32;l22;l52;l62;
	l52;l32;
	l52;l62;l52;// 第一场雪
	play(L3, 2, 2);
	
	l62;m11;l61;l61;m11; // 比2002
	l62;l61;l61;l52;l32;l52;l62; //年来的稍晚了一
	l52;l32;l52;l62; // 稍晚了一些
	play(L6, 2, 6);
	
	l52;//抓牌
	play(L5, 2, 2);
	
	l61;l51;//看牌
	play(L2, 4, 4);
	
	l32;l54;l32;//洗牌码牌
	play(L6, 4, 4);
	
	play(L1, 1, 0);//失败
	play(L1, 1, 2);
	
	m11;m11;m31;m31;//知道因为
	m22;m22;m31;m21;m22;//啥失败吗
	
	m32;m21;m21;m12;l72;//真让我替你
	l62;m32;m22;m12;//感到悲哀
	
	m61;m11;//不打针
	play(M3, 1, 1);
	m21;m11;//不吃药
	play(M2, 1, 1);
	
	m21;m31;m21;m31;m21;m11;m22;//坐着就是跟你唠
	play(M3, 1, 1); //用
	m21;m31;m21;m11; //谈话的方式
	play(M1, 1, 1);
	m21;m31;m21;m31;m12;l62; //治疗这叫话疗
	
	m22;m32;l62;m12; //现在请听第一个话题
	m21;m31;m21;m11;
	play(L6, 2, 2);
	
	//l62;m31;m31;m32;m12; //母猪的产后
	rap(4, -3, 1, 1);//母
	rap(5, 0, 1, 0);//猪
	rap(2, -1, 1, 0);//的
	rap(5, -2, 2, 0);//产
	rap(9, -8, 2, 0);//后
	
	l72;l32;l61;l61;l61;l61;//护理拿错书了
	
	m32;m12;m21;m11;l62;//粮食大丰收
	l52;l32;l51;l51;l62;//洪水被赶跑
	l62;m32;m21;m21;m11;m11;//百姓安居乐业
	l71;l71;l51;l61;m12;l62;//齐夸党的领导
	m32;m32;m21;l61;m11;m11;m11;m21;m11;m21;m12;l62; //国外比较乱套成天勾心斗角
	m32;m32;m31;m31;m31;m31;m21;m31;m21;m31;m12;l62; //纵观世界风云这边风景更好
	
	while(1);
}

void T_0() interrupt 1 {
	if (rapMode) {
		TH0 = rapc;
		TL0 = 0xFF;
	} else {
		TH0 = FRE_TH[musicOne + OFFSET];
		TL0 = FRE_TL[musicOne + OFFSET];
	}
  fmq = ~fmq;
}

void T_1() interrupt 3 {
	TH1 = T1H;
	TL1 = T1L;
	timerFlag++;
	if (rapMode) {
		if (rapn) {
			rapc = rapa - (rapb * timerFlag / t1m);
		} else {
			rapc = rapa + (rapb * timerFlag / t1m);
		}
	}
	if (timerFlag > t1m) {
		timerFlag = 0;
		timer = 0;
	}
}
