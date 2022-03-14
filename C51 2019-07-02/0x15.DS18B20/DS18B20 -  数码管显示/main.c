#include<reg52.h>
#include<ds18b20.h>


sbit LA=P2^2;
sbit LB=P2^3;
sbit LC=P2^4;

#define dula P0
#define count 50000
#define THx (65536-count)/256
#define TLx (65536-count)%256

bit flag = 0;
uchar code table[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x40};
uchar distab[7];
void datapros() {
  //  static 
		int temp = readc();
    float tp;
	//if(flag == 1)
   // temp = readc();

    if(temp< 0)
    {
        distab[0] = 0x40;
        temp=temp-1;
        temp=~temp;
        tp=temp;
        temp=tp*0.0625*100+0.5;
    }
    else
    {
        distab[0] = 0x00;
        tp=temp;
        temp=tp*0.0625*100+0.5;
    }
		if(temp >= 10000)
			distab[1] = table[temp/10000];
		else
			distab[1] = 0x00;
		
		if(temp >= 1000)
			distab[2] = table[temp/1000%10];
		else
			distab[2] = 0x00;
		
    distab[3] = table[temp/100%10];
    distab[4] = table[temp/10%10];
    distab[5] = table[temp%10];
    distab[6] = 0x39;

}
void display() {
    unsigned int i = 0;
    for(i = 0; i < 8; i++ ) {
        switch(i) {
        case 0:
            LC = 0;
            LB = 0;
            LA = 0;
            dula = distab[6];
            break;
        case 1:
            LC = 0;
            LB = 0;
            LA = 1;
            dula = distab[5];
            break;
        case 2:
            LC = 0;
            LB = 1;
            LA = 0;
            dula = distab[4];
            break;
        case 3:
            LC = 0;
            LB = 1;
            LA = 1;
            dula = distab[3] | 0x80;//Ð¡Êýµã
            break;
        case 4:
            LC = 1;
            LB = 0;
            LA = 0;
            dula = distab[2];
            break;
        case 5:
            LC = 1;
            LB = 0;
            LA = 1;
            dula = distab[1];
            break;
        case 6:
            LC = 1;
            LB = 1;
            LA = 0;
            dula = distab[0];
            break;
        case 7:
            LC = 1;
            LB = 1;
            LA = 1;
            dula = 0x00;
            break;
        }
        delay(100);
        dula = 0x00;
    }
}
void TIME_Init() {
	TMOD = 0X01;
	ET0 = 1;
	EA = 1;
	TH0 = (65536-50000)/256;
	TL0 = (65536-50000)%256;
	TR0 = 1;
}
void main() {
	TIME_Init();
    while(1) {
        display();
        datapros();
    }
}

void TIME0() interrupt 1
{
	static int i = 0;
	TH0 = (65536-50000)/256;
	TL0 = (65536-50000)%256;
	if(++i == 100) {
		i = 0;
		flag = ~flag;
	}
}





















