#include "dht11.h"
#include "delay.h"
	

static void DHT11_GPIO_Out(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   = DHT11_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
static void DHT11_GPIO_In(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin   = DHT11_PIN;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
static void DHT11_START(void) {
	DHT11_GPIO_Out();
	DHT11_IO = 1;
	delay_us(10); // 可有可无
	DHT11_IO = 0;
	delay_ms(20); //   18 ms的低电平 
	DHT11_IO = 1;
	delay_us(30); // 20~40us的高电平 
}

static uint8_t Receive_DHT11(void) {
	uint8_t i;
	uint8_t dat,temp;
	DHT11_GPIO_In();
	for(i=0;i<8;i++) {
		while(DHT11_IO_IN == 0);//等待50us的低电平开始信号结束
		delay_us(30);    //开始信号结束后，延时26us-28us
		temp=0;   //如果时间为26us-28us 则表示接收的数据为'0'
		if(DHT11_IO_IN==1)
			temp=1;//如果时间超过26us-28us 则表示收到的数据为'1'
		while(DHT11_IO_IN == 1);//等待数据信号高电平， '0'为26us-28us；'1'为70us
		dat<<=1;//将接收到的数向高位左移
		dat|=temp;
	}
	return dat;
}
void Receive_DATA(Temperature_AND_Humidity *Temperature_AND_humidity_Structure) //接收数据
{
	uint8_t R_H,R_L,T_H,T_L,check;          //设置准备校验存储温湿度的变量
	uint8_t i;

	DHT11_START();//开始信号初始化
	DHT11_IO=1;   //主机设为输入  判断从机DHT11的响应信号     
	DHT11_GPIO_In(); // 准备接收信号
	if(DHT11_IO_IN == RESET) //判断是否有响应信号
	{
		i = 0;
		while((DHT11_IO_IN == 0)&&(i<100)) {//等待 DHT11 80us 的响应信号 低电平 
			i++;
			delay_us(10);
		}
		i = 0;
		while((DHT11_IO_IN == 1)&&(i<100)) { // 等待DHT 拉高 的80us 高电平 
			i++;
			delay_us(10);
		}
		R_H   = Receive_DHT11();//湿度整数
		R_L   = Receive_DHT11();//湿度小数
		T_H   = Receive_DHT11();//温度整数
		T_L   = Receive_DHT11();//温度小数
		check = Receive_DHT11();//校验和
		DHT11_GPIO_Out();
		DHT11_IO=0;//当所有的数据接收完成后，将从机电平拉低50us
		delay_us(50);
		DHT11_IO=1;//将从机电平拉高，进入空闲状态

		if(R_H+R_L+T_H+T_L == check)//判断读取的数据与校验位是否相同
		{
			Temperature_AND_humidity_Structure->RH = R_H;
			Temperature_AND_humidity_Structure->RL = R_L;
			Temperature_AND_humidity_Structure->TH = T_H;
			Temperature_AND_humidity_Structure->TL = T_L;
		}
		
		Temperature_AND_humidity_Structure->TEMP[0] = Temperature_AND_humidity_Structure->TH/10+48;
		Temperature_AND_humidity_Structure->TEMP[1] = Temperature_AND_humidity_Structure->TH%10+48;
		Temperature_AND_humidity_Structure->TEMP[2] = '.';
		Temperature_AND_humidity_Structure->TEMP[3] = Temperature_AND_humidity_Structure->TL/10+48;
		Temperature_AND_humidity_Structure->TEMP[4] = Temperature_AND_humidity_Structure->TL%10+48;
		Temperature_AND_humidity_Structure->TEMP[5] = 95+32;
		Temperature_AND_humidity_Structure->TEMP[6] = '\0';
		
		Temperature_AND_humidity_Structure->HUM[0] = Temperature_AND_humidity_Structure->RH/10+48;
		Temperature_AND_humidity_Structure->HUM[1] = Temperature_AND_humidity_Structure->RH%10+48;
		Temperature_AND_humidity_Structure->HUM[2] = '.';
		Temperature_AND_humidity_Structure->HUM[3] = Temperature_AND_humidity_Structure->RL/10+48;
		Temperature_AND_humidity_Structure->HUM[4] = Temperature_AND_humidity_Structure->RL%10+48;
		Temperature_AND_humidity_Structure->HUM[5] = '%';
		Temperature_AND_humidity_Structure->HUM[6] = '\0';
		
		// 只显示两位，所显示数据没有精确到小数点后。
#if   !RESET
		Temperature_AND_humidity_Structure->TEMP[2] = 95+32;
		Temperature_AND_humidity_Structure->TEMP[3] = '\0';
		
		Temperature_AND_humidity_Structure->HUM[2] = '%';
		Temperature_AND_humidity_Structure->HUM[3] = '\0';
#endif
	
	}
}









