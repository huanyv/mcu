#include"STC89C5XRC.H"
sbit led=P2^0;

#define uchar unsigned char
#define uint unsigned int

#define count 100
#define THx (65535-count)/256
#define TLx (65535-count)%256

void TIM_Init() {
	EXEN2=0;//关闭T2EX的跳变
	C_T2=0;//使用定时器功能
	RCLK=TCLK=0;//
	TR2=1;//启动定时器
	EA=1;ET2=1;//打开中断

	RCAP2L=TL2=TLx;//低八位
	RCAP2H=TH2=THx;//高八位
}
void main(void){
	TIM_Init();
	while(1) {
		
	}
}
void TIM2() interrupt 5 {
	static uchar PWM_Count = 0;
	static uchar PWM_Value = 0;
	static bit PWM_Flag = 0;
	static uint PWM_Huxi = 0;
	TF2=0;
	PWM_Count++;
	PWM_Huxi++;
	if(PWM_Count == PWM_Value){
		led=1;
	}
	if(PWM_Count == 10){
		PWM_Count = 0;
		led=0;
	}
	if(PWM_Huxi>=500&&PWM_Flag==0){
		PWM_Huxi=0;
		PWM_Value++;
		if(PWM_Value>9)
			PWM_Flag=1;
	}
	if(PWM_Huxi>=500&&PWM_Flag==1){
		PWM_Huxi=0;
		PWM_Value--;
		if(PWM_Value<1)
			PWM_Flag=0;
	}
}


	