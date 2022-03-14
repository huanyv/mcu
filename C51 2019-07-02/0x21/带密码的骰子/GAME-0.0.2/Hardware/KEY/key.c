#include"reg52.h"
#include"key.h"

uchar Read_Key() {
	static uchar key_state = 0;
	static uint key_time = 0;
	uchar key_return = 0;
	uchar key_count = 0;
	KEY = 0xf0;
	key_count = KEY;
	switch(key_state) {
		case 0:
			if(key_count!=0xf0) {
				key_state = 1;
				key_time = 0;
			}break;
		case 1:
			if(key_count != 0xf0) {
				key_time++;
				if(key_time>=10) {
					
					KEY = 0x0f;
					key_count |= KEY;
					
					switch(key_count) {
						case 0x77:key_return=1; break;
						case 0x7b:key_return=2; break;
						case 0x7d:key_return=3; break;
						case 0x7e:key_return=4; break;
                                    
						case 0xb7:key_return=5; break;
						case 0xbb:key_return=6; break;
						case 0xbd:key_return=7; break;
						case 0xbe:key_return=8; break;
                                    
						case 0xd7:key_return=9; break;
						case 0xdb:key_return=10;break;
						case 0xdd:key_return=11;break;
						case 0xde:key_return=12;break;
						
						case 0xe7:key_return=13;break;
						case 0xeb:key_return=14;break;
						case 0xed:key_return=15;break;
						case 0xee:key_return=16;break;
					}
					key_state = 2;
				}
			}
			else {
					key_state = 0;
			}break;
		case 2:
			if(key_count == 0xf0) {
				key_state = 0;
			}break;
	}
	return key_return;
}


