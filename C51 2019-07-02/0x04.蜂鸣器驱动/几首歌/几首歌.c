#include <reg52.h>
sbit speaker = P1^5;
unsigned char timer0h, timer0l, time;
//--------------------------------------
//单片机晶振采用11.0592MHz
// 频率-半周期数据表 高八位 本软件共保存了四个八度的28个频率数据
code unsigned char FREQH[] = {
    0xF2, 0xF3, 0xF5, 0xF5, 0xF6, 0xF7, 0xF8, //低音1234567
    0xF9, 0xF9, 0xFA, 0xFA, 0xFB, 0xFB, 0xFC, 0xFC,//1,2,3,4,5,6,7,i
    0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE, //高音 234567
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF
}; //超高音 1234567
// 频率-半周期数据表 低八位
code unsigned char FREQL[] = {
    0x42, 0xC1, 0x17, 0xB6, 0xD0, 0xD1, 0xB6, //低音1234567
    0x21, 0xE1, 0x8C, 0xD8, 0x68, 0xE9, 0x5B, 0x8F, //1,2,3,4,5,6,7,i
    0xEE, 0x44, 0x6B, 0xB4, 0xF4, 0x2D, //高音 234567
    0x47, 0x77, 0xA2, 0xB6, 0xDA, 0xFA, 0x16
}; //超高音 1234567
//--------------------------------------
//code unsigned char sszymmh[] = {
//	3,2,1, 0,2,1, 0,2,1, 3,2,1, 0,2,2, 3,2,1, 0,2,2, 3,2,1, 0,2,1, 3,2,1, 0,2,1, 1,2,1, 0,2,1,  
//    0,0,0
//};          //China-X	  未完成  	


code unsigned char sszymmh[] = {
    5,2,1, 5,2,1, 3,2,1, 2,2,1, 3,2,1, 6,1,2, //天青色 等烟雨
    2,2,1, 3,2,1, 5,2,1, 3,2,1, 2,2,3,
    5,2,1, 5,2,1, 3,2,1, 2,2,1, 3,2,1, 5,1,2,
    2,2,1, 3,2,1, 5,2,1, 3,2,1, 1,2,3,
    1,2,1, 2,2,1, 3,2,1, 5,2,1, 6,2,1, 5,2,1, 3,2,1, 5,2,1, 3,2,1, 3,2,1, 2,2,1, 2,2,2,
    1,2,1, 2,2,1, 1,2,1, 2,2,2, 1,2,1, 2,2,2, 3,2,2, 5,2,2, 3,2,2, 3,2,2,
    5,2,1, 5,2,1, 3,2,1, 2,2,1, 3,2,1, 6,1,2,
    2,2,1, 3,2,1, 5,2,1, 3,2,1, 2,2,3,
    5,2,1, 5,2,1, 3,2,1, 2,2,1, 3,2,1, 5,1,2,
    2,2,1, 3,2,1, 5,2,1, 3,2,1, 1,2,3,
    1,2,1, 2,2,1, 3,2,1, 5,2,1, 6,2,1, 5,2,1, 3,2,1, 5,2,1, 3,2,1, 3,2,1, 2,2,1, 2,2,2,
    5,1,1, 3,2,2, 2,2,2, 2,2,2, 1,2,1,  	//你眼带笑意
    0,0,0
};            //青花瓷 HOOK      		*/


//	code unsigned char sszymmh[] = {1,2,3,2,2,1,6,1,1,1,2,1,5,1,2,5,2,3,1,3,1,6,2,1,5,2,1,3,2,1,5
//		,2,1,2,2,4,2,2,3,3,2,1,7,1,2,6,1,2,5,1,3,6,1,1,1,2,2,2,2,2,3,1,2,1,2,2,6,1,1,5,1,1,6,1,1,1,2,1,5,
//			1,4,3,2,3,5,2,1,7,1,2,2,2,2,6,1,1,1,2,1,5,1,4,3,1,1,5,1,2,3,1,2,5,1,1,6,1,1,7,1,1,2,2,1,6,1,
//			4,5,1,1,6,1,1,1,2,3,2,2,1,5,2,2,3,2,2,2,2,2,3,2,1,2,2,1,1,2,2,6,1,1,5,1,1,3,1,2,3,1,4,1,2,4,6,
//			1,3,1,2,1,6,1,1,5,1,1,3,1,1,5,1,1,6,1,1,1,2,1,5,1,4,0, 0, 0};      //   梁祝


/*	code unsigned char sszymmh[] = {5,1,1, 1,2,3, 1,2,1, 1,2,1, 1,2,1, 5,1,1, 6,1,1, 7,1,1, 1,2,2, 1,2,2,
		3,2,1, 1,2,1, 2,2,1, 3,2,1, 5,2,2, 5,2,1, 5,2,2,
		3,2,2, 3,2,1, 1,2,2, 3,2,1, 5,2,2, 3,2,1, 2,2,2, 2,2,4,
		6,2,2,5,2,2,2,2,2,3,2,2,5,2,1,3,2,2,5,2,1,3,2,1,2,2,1,3,2,1,1,2,1,2,2,1,3,2,2,
		5,2,2,6,1,1,1,2,1,1,2,1,3,2,2,3,2,1,5,2,2,5,2,1,2,2,1,2,2,1,2,2,1,6,1,1,6,1,1,2,2,4,
		5,1,1,1,2,3,1,2,1,3,2,3,3,2,1,5,2,4,5,2,4,
		1,2,2,3,2,1,5,2,1,5,1,1,6,2,2,5,2,2,
		3,2,2,1,2,1,5,2,1,5,2,1,5,2,1,3,2,1,1,2,1,5,1,2,1,2,2,
		3,1,1,1,1,1,5,2,1,5,2,1,5,2,1,3,2,1,1,2,1,5,1,2,1,2,2,5,1,2,1,2,2,5,1,2,1,2,2,1,2,2,
		0, 0, 0* };//国歌 */
		
		
//		code unsigned char sszymmh[] = {6,2,3,5,2,1,3,2,2,5,2,2,6,2,1,6,2,2,5,2,1,3,2,4,6,1,3,1,2,1,2,2,2,5,2,1,3,2,1,2,2,4,
//		6,2,3,2,3,1,2,3,2,1,3,1,7,2,1,6,2,3,5,2,1,3,2,4,2,2,1,5,2,1,5,2,1,3,2,1,2,2,1,3,2,1,1,2,1,7,1,1,6,1,4,
//		1,2,3,6,1,1,6,2,1,1,2,2,2,2,2,5,
//		2,1,3,2,1,2,2,4,5,2,3,3,2,1,3,2,
//		2,5,2,2,6,2,4,2,3,3,2,3,1,1,3,2,
//		2,3,2,6,2,1,1,3,1,5,2,1,6,2,1,3,
//		2,4,2,2,1,5,2,1,5,2,1,3,2,1,2,2,
//		1,3,2,1,1,2,1,7,1,1,6,1,4,
//		0, 0, 0};//虞美人 */
		
		
		
//结束标记
//世上只有妈妈好数据表 要想演奏不同的乐曲, 只需要修改这个数据表
//code unsigned char sszymmh[] = {
//6, 2, 3, 5, 2, 1, 3, 2, 2, 5, 2, 2, 1, 3, 2, 6, 2, 1, 5, 2, 1,
//一个音符有三个数字。前为第几个音、中为第几个八度、后为时长（以半拍为单位）。
//6, 2, 3代表：6, 中音, 3个半拍;
//5, 2, 1代表：5, 中音, 1个半拍;
//3, 2, 2代表：3, 中音, 2个半拍;
//5, 2, 2代表：5, 中音, 2个半拍;
//1, 3, 2代表：1, 高音, 2个半拍;
//
//6, 2, 4, 3, 2, 2, 5, 2, 1, 6, 2, 1, 5, 2, 2, 3, 2, 2, 1, 2, 1,
//6, 1, 1, 5, 2, 1, 3, 2, 1, 2, 2, 4, 2, 2, 3, 3, 2, 1, 5, 2, 2,
//5, 2, 1, 6, 2, 1, 3, 2, 2, 2, 2, 2, 1, 2, 4, 5, 2, 3, 3, 2, 1,
//2, 2, 1, 1, 2, 1, 6, 1, 1, 1, 2, 1, 5, 1, 6, 0, 0, 0,,,,,,,,,,,,,,,,,,,,,6,2,3, 6,2,1, 1,3,2, 7,2,1, 6,2,1, 5,2,2, 3,2,1, 5,2,1, 6,2,4, 3,2,3,};
//--------------------------------------
void t0int() interrupt 1 //T0中断程序，控制发音的音调
{
    TR0 = 0; //先关闭T0
    speaker = !speaker; //输出方波, 发音
    TH0 = timer0h; //下次的中断时间, 这个时间, 控制音调高低
    TL0 = timer0l;
    TR0 = 1; //启动T0
}
//--------------------------------------
void delay(unsigned char t) //延时程序，控制发音的时间长度
{
    unsigned char t1;
    unsigned long t2;
    for(t1 = 0; t1 < t; t1++) //双重循环, 共延时t个半拍
        for(t2 = 0; t2 < 3000; t2++); //延时期间, 可进入T0中断去发音
    TR0 = 0; //关闭T0, 停止发音
}
//--------------------------------------
void song() //演奏一个音符
{
    TH0 = timer0h; //控制音调
    TL0 = timer0l;
    TR0 = 1; //启动T0, 由T0输出方波去发音
    delay(time); //控制时间长度
}
//--------------------------------------
void main(void)
{
    unsigned char k, i;
    TMOD = 1; //置T0定时工作方式1
    ET0 = 1; //开T0中断
    EA = 1; //开CPU中断
    while(1) {
        i = 0;
        time = 1;
        while(time) {
            k = sszymmh[i] + 7 * sszymmh[i + 1] - 1;
            //第i个是音符, 第i+1个是第几个八度
            timer0h = FREQH[k]; //从数据表中读出频率数值
            timer0l = FREQL[k]; //实际上, 是定时的时间长度
            time = sszymmh[i + 2]; //读出时间长度数值
            i += 3;
            song(); //发出一个音符
        }
    }
}
/*======================================
应网友要求，下面再详细写一下乐谱和数据的转换关系。
以李叔同大师的《送别》的前二小节来说明转换的方法。
这部分的歌词是："长 亭 外， 古 道 边，"；
这部分的乐谱是：| 5 35 1 － | 6 16 5 － |。
（注意：乐谱中的1是高音，上边是带点的；还有些音符，应该有下划线，在这里都无法标出。感兴趣的网友应该去查看正规的乐谱。）
那么，据此就可以写出《送别》前二小节的数据表：
//--------------------------------------*/
//code unsigned char sszymmh[] = {
//5, 2, 2, 3, 2, 1, 5, 2, 1, 1, 3, 4,
//嗦,中音,2个半拍;　咪,中音,1个半拍;　嗦,中音,1个半拍;　哆,高音,4个半拍
//6, 2, 2, 1, 3, 1, 6, 2, 1, 5, 2, 4,
//啦,中音,2个半拍;　哆,高音,1个半拍;　啦,中音,1个半拍;　嗦,中音,4个半拍
//0, 0, 0};
//结束标记
/*--------------------------------------
记住：三个数字一组，代表一个音符。
第一个数字是1234567之一，代表音符哆来咪发...；
第二个数字是0123之一，代表低音、中音、高音、超高音；
第三个数字是半拍的个数，代表时间长度。
当三个数字都是0，就代表乐曲数据表的结尾。
用这个数据表，替换掉程序中《世上只有妈妈好》的数据表，本程序就可以播放《送别》的前两小节。
*/