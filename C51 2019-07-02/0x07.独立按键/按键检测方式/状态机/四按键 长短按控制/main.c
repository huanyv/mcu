#include"stc89c5xrc.h"
typedef unsigned char uchar;
typedef unsigned int uint;

sbit led1=P2^3;
sbit led2=P2^2;
sbit led3=P2^1;
sbit led4=P2^0;
sbit led5=P2^7;
sbit led6=P2^6;
sbit led7=P2^5;
sbit led8=P2^4;


//uchar read_key(){
//	static uint key_time=0;
//	static uchar key_state=0;
//	uchar key_count=0;
//	uchar key_return=0;
//	key_count=P3&0x0f;
//	switch(key_state){
//		case 0:
//			if(key_count!=0x0f){
//				key_time=0;
//				key_state=1;
//			}break;
//		case 1:
//			if(key_count!=0x0f){
//				key_time++;
//				if(key_time>60000){
//					key_state=2;
//					switch(key_count){
//						case 0x0d:key_return=1;break;
//						case 0x0e:key_return=2;break;
//						case 0x0b:key_return=3;break;
//						case 0x07:key_return=4;break;
//					}
//				}
//			}
//			else{
//				key_state=0;
//			}break;
//		case 2:
//			if(key_count==0x0f){
//				key_return=0;
//				key_state=0;
//			}break;
//	}
//	return key_return;
//}
uchar read_key(){
	static uint key_time=0;//长短按时间判断
	static uchar key_state=0;//状态
	
	uchar key_count=0;//读键值 变量
	static uchar key_count2=0;//判断按键变量
	
	uchar key_return=0;//返回键值
	key_count=P3&0x0f;//读键值
	switch(key_state){
		case 0:
			if(key_count!=0x0f){
				key_time=0;
				key_count2=0;
				key_state=1;
			}break;
		case 1:
			if(key_count!=0x0f){
				key_time++;
				if(key_time>500){
					key_count2=key_count;
					key_state=2;
				}
			}
			else{
				key_state=0;
			}break;
		case 2:
			if(key_count==0x0f){
				switch(key_count2){
					case 0x0d:key_return=1;break;
					case 0x0e:key_return=2;break;
					case 0x0b:key_return=3;break;
					case 0x07:key_return=4;break;
				}
				key_state=0;
			}
			if(key_count!=0x0f){
				key_time++;
				if(key_time>20000){
					switch(key_count){
						case 0x0d:key_return=11;break;
						case 0x0e:key_return=22;break;
						case 0x0b:key_return=33;break;
						case 0x07:key_return=44;break;
					}
					key_state=3;
				}
			}break;
			case 3:
				if(key_count==0x0f){
					key_state=0;
				}break;
	}
	return key_return;
}

void main(void){
	uchar temp=0;
	while(1){
		temp=read_key();
		if(temp==1){
			led1=~led1;
		}
		if(temp==2){
			led2=~led2;
		}
		if(temp==3){
			led3=~led3;
		}
		if(temp==4){
			led4=~led4;
		}
		if(temp==11){
			led5=~led5;
		}
		if(temp==22){
			led6=~led6;
		}
		if(temp==33){
			led7=~led7;
		}
		if(temp==44){
			led8=~led8;
		}
	}
}




















