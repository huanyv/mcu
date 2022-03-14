#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define RxIn 90              //定义接收的数组长度为90
uchar code AT[]="AT";              //握手信号
uchar code ATE[]="ATE";              //关回显
uchar code AT_CNMI[]="AT+CNMI=2,1";//设置这组参数来了新信息直接显示到串口，不作存储
uchar code AT_CSCA[]="AT+CSCA=\"+8613800571500\"";//设置服务中心号码              AT+CSCA=\"+8613010360500\"
uchar code AT_CMGF[]="AT+CMGF=1";//设置短信的格式为text格式
uchar code AT_CMGR[]="AT+CMGR=";//读取短信指令
uchar code AT_CMGS[]="AT+CMGS=";//发送短信指令
uchar code AT_CMGD[]="AT+CMGD=";//发送短信指令
uchar AT_delete[12];
uchar AT_Read[12];              //用来存储发送读取短信指令
uchar AT_SendNumber[22];  //用来存储发送短信号码指令
uchar numberbuf[3];                            //用来保存短信条数
uchar idata SystemBuf[RxIn];  //储存出口接收数据
uchar CommandBuf[4];              //用来储存指令
uchar Rx=0;
bit receiveready=0;                               //接收短信标志位
bit sendready=0;                               //发送短信准备标志位
bit send=0;                                                           //发送短信标志位
sbit IGT=P2^7;//启动GSM的启动线连IGT
sbit sw1=P3^3; //打电话
sbit sw2=P3^4;              //发测试短信
sbit sw3=P3^5;              //发温度
sbit beep=P3^2;    //蜂鸣器
void Delay_ms(uint i);
void Start_GSM(void);
void UART_init (void);
void sendchar(uchar ch);
void sendstring(uchar *p);
void GSM_INIT(void);
void receive_ready(void);
void message_read(void);
void read_message(void);
void sendmessage(void);

uchar code  AT7[]= {0x41,0x54,0x2B,0x43,0x4D,0x47,0x53,0x3D}; //AT+CMGS=  AT+CMGS=“+8613xxxxxxxxx”回车>输入短消息。Crtl+Z结束并发送。
uchar code  AT12[]= {0x41,0x54,0x44,0x3E}; //ATD> ATD*****; （拨号,"*"为需要拨的号码,如呼叫13973292929,则为ATD13973292929;
uchar  code  neirong[11]="15158107675";                                          //13185018567

sbit DQ=P3^7;                                                           //DS18B20数据传输线接单片机的相应的引脚
unsigned char tempL=0;                                           //临时变量低位
unsigned char tempH=0;                                          //临时变量高位
float temperature;                                               //温度值
unsigned char k,ge,shi,bai;
uchar code  atshanchu[]= { "AT+CMGD=9"};

sbit lcdrs=P1^0;
sbit lcdrw=P1^1;
sbit lcden=P1^2;
void delaymm(uint z)
{
    uint x,y;
    for(x=z; x>0; x--)
        for(y=110; y>0; y--);
}
void delay(unsigned int k)
{
    unsigned int n;
    n=0;
    while(n < k)
    {
        n++;
    }
    return;
}
void write_cmd(uchar cmd)
{
    lcden=0;
    lcdrs=0;
    lcdrw=0;
    P0=cmd;
    _nop_();
    lcden=1;
    delaymm(1);
    lcden=0;
    _nop_();
}
void write_dat(uchar dat)
{
    lcden=0;
    lcdrs=1;
    P0=dat;
    _nop_();
    lcden=1;
    delaymm(1);
    lcden=0;
    _nop_();
}
void lcdint()
{
    lcden=0;
    write_cmd(0x38);
    write_cmd(0x0c);
    write_cmd(0x06);
    write_cmd(0x01);
    delaymm(5);
}
ReadOneChar(void)                /*函数功能:向DS18B20读一字节数据*/
{
    unsigned char i=0;
    unsigned char dat=0;
    for (i=8; i>0; i--)
    {
        DQ=1;
        delay(1);
        DQ=0;
        dat>>=1;
        DQ=1;
        if(DQ)
            dat|=0x80;
        delay(4);
    }
    return(dat);
}
void WriteOneChar(unsigned char dat) /*函数功能:向DS18B20写一字节数据*/
{
    unsigned char i=0;
    for(i=8; i>0; i--)
    {
        DQ=0;
        DQ=dat&0x01;
        delay(5);
        DQ=1;
        dat>>=1;
    }
    delay(4);
}
void Init_DS18B20(void)/*函数功能:DS18B20初始化子程序*/
{
    unsigned char x=0;
    DQ=1;                                                    //DQ先置高
    delay(8);                          //延时
    DQ=0;                                         //发送复位脉冲
    delay(85);                                    //延时（>480ms)
    DQ=1;                                                    //拉高数据线
    delay(14);                                   //等待（15~60ms)
}
ReadTemperature(void) /*函数功能:向DS18B20读温度值*/
{
    Init_DS18B20();                                            //初始化
    WriteOneChar(0xcc);                              //跳过读序列号的操作
    WriteOneChar(0x44);                             //启动温度转换
    delaymm(125);                                                           //转换需要一点时间，延时
    Init_DS18B20();                                            //初始化
    WriteOneChar(0xcc);                              //跳过读序列号的操作
    WriteOneChar(0xbe);                             //读温度寄存器（头两个值分别为温度的低位和高位）
    delaymm(125);
    tempL=ReadOneChar();                             //读出温度的低位LSB
    tempH=ReadOneChar();                             //读出温度的高位MSB
    //温度转换，把高低位做相应的运算转化为实际温度
    temperature=((tempH*256)+tempL)*0.0625;
    delay(200);
    return(temperature);
}
void senddata(uchar dat) /*发送数据函数*/
{
    SBUF =dat;
    while(!TI);
    TI = 0;
}
void mingling(uchar zijie,uchar *p)              /*发送数组函数*/
{   uchar m;
    for(m=0; m<zijie; m++)senddata(p[m]);
}
void Delay_ms(uint i)              /*毫秒延时*/
{
    unsigned int j;
    for(; i>0; i--)
    {
        for(j=0; j<125; j++)
        {
            ;
        }
    }
}
/*启动TC35,在 15脚IGT加时长至少为100ms的低电平,该信号下降沿时间小于1ms。启动后，15 脚的信号保持高电平*/
void Start_GSM(void)
{
    IGT=0;
    Delay_ms(1000);
    IGT=1;
    Delay_ms(1000);
}
void UART_init (void) /*对串口进行初始化*/
{
    TMOD=0x20;              //选择定时器1
    PCON=0x00;              ///波特率不加倍
    SCON=0x50;              //串行工作方式1允许串行接收
    TH1=0xFD;              //实验板上晶振位11.0592MHZ,选择波特率为9600
    TL1=0xFD;              //在相应计数器上赋值
    EA=1;                            //总中断开启
    ES=1;                            //串行中断开启
    TR1=1;                            //开启定时器1

}
void sendchar(uchar ch)/*单片机发送一字节数据*/
{
    SBUF=ch;
    while(TI==0);
    TI=0;
}
void sendstring(uchar *p) /*通过串口发送字符串*/
{

    while(*p)
    {
        sendchar(*p);
        p++;
    }
    sendchar(0x0D);
    sendchar(0x0A);
}
void receive(void) interrupt 4 using 1              /*通过中断，串口接收数据*/
{

    if(RI)
    {

        if(Rx<RxIn)
        {
            SystemBuf[Rx]=SBUF;
            Rx++;
        }

        RI=0;
    }
}
void GSM_INIT(void)              /*初始化TC35模块*/
{
LOOP:
    Delay_ms(1000);
    sendstring(AT);
    Delay_ms(1000);
    sendstring(ATE);
    Delay_ms(1000);
    sendstring(AT_CNMI);
    Delay_ms(1000);
    sendstring(AT_CSCA);
    Delay_ms(1000);
    for(Rx=0; Rx<RxIn; Rx++)
    {
        SystemBuf[Rx]=0x00;
    }
    Rx=0;
    sendstring(AT_CMGF);
    Delay_ms(1000);
    if((SystemBuf[2]=='O')&&(SystemBuf[3]=='K'))              //判断是否模块初始化成功,成功的话模块会回复"OK"给单片机
    {   //如果单片机没有收到OK,就继续发送初始化指令/
        for(Rx=0; Rx<RxIn; Rx++)
        {
            SystemBuf[Rx]=0x00;
        }
        Rx=0;
    }
    else
    {

        for(Rx=0; Rx<RxIn; Rx++)
        {
            SystemBuf[Rx]=0x00;
        }
        Rx=0;
        goto LOOP;
    }
}
void receive_ready(void)  /*接收短信准备*/
{
    uchar i;
    if((SystemBuf[5]==0x54)&&SystemBuf[6]==0x49)                            //如果有新短信来,模块会通过串口向单片机发送字符串,              TI
    {   //              此函数的功能是判断是否有新短信来,如果来的话就置位准备接受位标志为1
        receiveready=1;                                                                                                                              //如果不是新短信的指令,就舍弃,并将接收数组清零
        /*              write_cmd(0x01);
                      write_cmd(0x80);
                      for(i=0;i<16;i++)
                      {
                      write_dat(SystemBuf[i]);
                      delaymm(1);
                      }
                      write_cmd(0xc0);
                      for(i=16;i<32;i++)
                      {
                      write_dat(SystemBuf[i]);
                      delaymm(1);
                      }                                           //返回的是&&+CMTI: "SM",10  10表示我当前的短信数，说明我之前有9条，加上现在的共10条
                      while(1);               //删除短信的话我不会把以前存在卡里的短信的删掉              */
    }
    else {
        for(i=0; i<Rx; i++)
        {
            SystemBuf[i]=0x00;
        }
        Rx=0;
    }
}
void message_read(void) /*准备是否回复短信给目标号码*/
{

    if((sendready==1)&&(SystemBuf[5]==0x47)&&(SystemBuf[6]==0x52))
        send=1;
}
void read_message(void) /*发送读取短信指令*/
{
    uchar i;
    Delay_ms(1000);
    for(i=0; i<3; i++)
    {
        numberbuf[i]=SystemBuf[14+i]; //读走，10
    }

    for(i=0; i<8; i++)
    {
        AT_Read[i]=AT_CMGR[i];              //读取短信指令
    }
    for(i=8; i<11; i++)
    {
        AT_Read[i]=numberbuf[i-8];              //读走，10,是地址
    }
    for(Rx=0; Rx<RxIn; Rx++)
    {
        SystemBuf[Rx]=0x00;
    }
    Rx=0;
    sendstring(AT_Read);                                                                                       //发送AT+CMGR=，10  10代表短信储存所在位置

}
void readcommend(void)                /*读取短信内容,判断相应指令是否正确*/
{
    uchar i;
    for(i=0; i<4; i++)                                                                                                                                                                                       //将短信内容中的指令部分截取出来放到
    {   //CommandBuf数组中
        CommandBuf[i]=SystemBuf[64+i];
    }
    if((CommandBuf[0]=='b')&&(CommandBuf[1]=='a')&&(CommandBuf[2]=='n')&&(CommandBuf[3]=='g'))  //判断指令是否为开发光管指令
    {
        write_cmd(0x01);   //测试接收
        write_cmd(0x80);
        write_dat('b');
        write_dat('a');
        write_dat('n');
        write_dat('g');
        sendmessage();
    }                                                                                    //如果发送的指令既不是bang就定义为错误操作,不干别的
}
void delete_message(void)              /*删除短信指令*/
{
    uchar i;
    Delay_ms(1000);
    Delay_ms(1000);
    Delay_ms(5000);
    for(i=0; i<8; i++)
    {
        AT_delete[i]=AT_CMGD[i];
    }
    for(i=8; i<11; i++)
    {
        AT_delete[i]=numberbuf[i-8];
    }
    for(Rx=0; Rx<RxIn; Rx++)
    {
        SystemBuf[Rx]=0x00;
    }
    Rx=0;
    sendstring(AT_delete);                                                                                       //发送AT+CMGR=,??   ??代表短信储存所在位置

}
void sendmessage(void)              /*发送回复短信指令*/
{
    uchar i;
    for(i=0; i<8; i++)
    {
        AT_SendNumber[i]=AT_CMGS[i];
    }
    for(i=8; i<19; i++)
    {
        AT_SendNumber[i]=SystemBuf[18+i];              //位置26~36  将对方号码提取用来回复给对方
    }
    sendstring(AT_SendNumber);
    senddata(0x0d);
    delaymm(100);
    senddata('P');
    senddata('H');
    senddata('=');
    senddata('7');
    senddata('.');
    senddata('0');//内容
    senddata(0x20);
    senddata(0x1a);
    senddata(0x0d);
    Delay_ms(30);
}
void main()
{
    uchar x;
    uchar i;
    lcdint();
    Start_GSM();                                                        //开启TC35
    Delay_ms(10000);                                          //延时大约10秒 ,等待模块联网/
    UART_init();                                                        //串口初始化/
    GSM_INIT();                                                        //对tc35模块进行初始化
    write_cmd(0x80);
    write_dat('r');
    write_dat('e');
    write_dat('a');
    write_dat('d');
    write_dat('y');
    Delay_ms(1000);
    while(1)
    {
        if (!sw1)
        {
            Delay_ms(5);
            if(!sw1)
            {
                write_cmd(0x01);
                write_cmd(0x80);
                write_dat('r');
                write_dat('i');
                write_dat('n');
                write_dat('g');
                mingling(3,AT12);
                for(x=0; x<11; x++)senddata(neirong[x]);
                senddata(0x3b);
                senddata(0x0D);
                while(sw1==0);
                senddata(0x0D);              //发0x0d停止打电话
            }
        }
        if (!sw2)   //短信读取温度值
        {
            Delay_ms(5);
            if(!sw2)
            {
                while(sw2==0);
                k=ReadTemperature();
                delaymm(500);
                k=ReadTemperature();
                bai=(k%1000)/100;
                shi=(k%100)/10;
                ge=k%10;
                write_cmd(0x01);
                write_cmd(0x80);
                write_dat(0x30+bai);
                write_dat(0x30+shi);
                write_dat(0x30+ge);
                ES=0;
                mingling(8,AT7);
                for(i=0; i<11; i++)senddata(neirong[i]);
                senddata(0x0d);
                delaymm(100);
                senddata(shi+0x30);
                senddata(ge+0x30); //发送数据内容
                senddata(0x20);
                senddata(0x1a);
                senddata(0x0d);
                ES=1;
                delaymm(15000);
                ES=0;
                mingling(9,atshanchu);
                senddata(0x0D);
                ES=1;
                delaymm(2500);//删除短信，不过本来就没存到9
            }
        }
        if (!sw3)  //发送测试短信
        {
            Delay_ms(500);
            if(!sw3)
            {
                while(sw3==0);
                write_cmd(0x01);
                write_cmd(0x80);
                write_dat('t');
                write_dat('e');
                write_dat('x');
                write_dat('t');
                ES=0;
                mingling(8,AT7);
                for(i=0; i<11; i++)senddata(neirong[i]);
                senddata(0x0d);
                delaymm(100);
                senddata('C');
                senddata('A');
                senddata('I');
                senddata(0x20);
                senddata(0x1a);
                senddata(0x0d);
                ES=1;
                delaymm(15000);
                ES=0;
                mingling(9,atshanchu);
                senddata(0x0D);
                ES=1;
                delaymm(2500);
            }

        }
        receive_ready();
        if(receiveready==1)
        {
            read_message();
            receiveready=0;
            sendready=1;
        }
        Delay_ms(300);
        message_read();
        if(send==1)
        {
            /*              write_cmd(0x01);
                                   write_cmd(0x80);
                                   for(i=64;i<80;i++)
                                   {
                                   write_dat(SystemBuf[i]);
                                   delaymm(1);
                                   }
                                   write_cmd(0xc0);
                                   for(i=80;i<91;i++)
                                   {
                                   write_dat(SystemBuf[i]);
                                   delaymm(1);
                                   }
                        while(1);//读出来看下,结果是
                     //&&+CMGR: "REC UN                0~15
                     //READ","+86151581                16~31

                     //07680",,"11/06/1                32~47
                     //1,14:01:09+32"&&                48~63

                     //1234567891234567   64~79
                     //8912345678                      80~89              */

            Delay_ms(2000);
            readcommend();//检测密码，如果对就发送要发的东西
            Delay_ms(1000);
            delete_message();
            for(Rx=0; Rx<RxIn; Rx++)                                                                                    //每一次操作完成后对接收数组清零//
            {
                SystemBuf[Rx]=0x00;
            }
            Rx=0;
            send=0;
        }
    }
}