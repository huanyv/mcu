#include <REG52.H>
typedef unsigned char uchar;
typedef unsigned int uint;
#define led P1
void delay(uint i){
	while(i--);
}
void main(void){
	uchar dat = 0;
	while(1){
		for(dat = 0xff;dat != 0x00;dat = (dat >> 1) & 0x7f){
			for(led = 0xfe;led != dat;led = led << 1 | 0x01){
				led &= dat ;
				delay(30000);
			}
		}
		
	}
}