#include"intrins.h"
#include"reg52.h"
#include"DHT11.h"

#	define   delay_10us()     _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_()


void delay_1ms(uint i) {
    unsigned int x;
    while(i--)
        for(x=0; x<123; x++);
}

//初始化
void start()//开始信号
{
    IO=1;
    delay_10us();
    IO=0;
    delay_1ms(20);  //拉低至少 18ms  保证能检测到起始信号
    IO=1;          //检测到开始信号后，将电平拉高20-40us
    delay_10us();        //延时20-40us
    delay_10us();
    delay_10us();
    delay_10us();
}
uchar receive_byte()//接收一个字节
{
		uchar data_byte;
    uchar i,temp;
    for(i=0; i<8; i++)
    {
        while(!IO);//等待50us的低电平开始信号结束
        delay_10us();    //开始信号结束后，延时26us-28us
        delay_10us();
        delay_10us();
        temp=0;   //如果时间为26us-28us 则表示接收的数据为'0'
        if(IO==1)
            temp=1;//如果时间超过26us-28us 则表示收到的数据为'1'
        while(IO);//等待数据信号高电平， '0'为26us-28us；'1'为70us
        data_byte<<=1;//将接收到的数据向高位左移
        data_byte|=temp;
    }
    return data_byte;
}

void receive(int *temp,int *hum) //接收数据
{
	uchar RH,RL,TH,TL;              //设置存储温湿度的变量
	uchar R_H,R_L,T_H,T_L,check;          //设置准备校验存储温湿度的变量
	uchar i;

	start();//开始信号初始化
	IO=1;   //主机设为输入  判断从机DHT11的响应信号             
	if(IO == RESET) //判断是否有响应信号
	{
		i = 0;
		while((IO == 0)&&(i<100))//判断从机发出80us低电平信号是否结束
			i++;
		i = 0;
		while((IO == 1)&&(i<100))
			i++;

		R_H = receive_byte();//湿度整数
		R_L = receive_byte();//湿度小数
		T_H = receive_byte();//温度整数
		T_L = receive_byte();//温度小数
		check = receive_byte();//校验和
		
		IO=0;//当所有的数据接收完成后，将从机电平拉低50us
		delay_10us();        //拉低50us
		delay_10us();
		delay_10us();
		delay_10us();
		delay_10us();
		IO=1;//将从机电平拉高，进入空闲状态

		if(R_H+R_L+T_H+T_L == check)//判断读取的数据与校验位是否相同
		{
			RH=R_H;
			RL=R_L;
			TH=T_H;
			TL=T_L;
		}
		*temp   = TH;
		*temp <<= 8;
		*temp  |= TL;

		*hum   =  RH;
		*hum <<=  8;
		*hum  |=  RL;
	}
}