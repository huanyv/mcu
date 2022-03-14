#include "key.h"


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
				if(key_time>1){
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
				if(key_time>90){
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





















