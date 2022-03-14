#include"reg52.h"
#include"key.h"



uchar Read_Key() {
	static uchar KEY_STATE  = 0;
	static uint  KEY_TIME   = 0;
	uchar KEY_COUNT  = 0;	
	uchar KEY_RETURN = 0;
	KEY_COUNT = 0x3c & P2;
	switch(KEY_STATE) {
		case 0:
			if(KEY_COUNT!=0x3c) {
				KEY_STATE = 1;
				KEY_TIME  = 0;
			}break;
		case 1:
			if(KEY_COUNT!=0x3c) {
				KEY_TIME++;
				if(KEY_TIME>15) {
					switch(KEY_COUNT) {
						case 0x1c:KEY_RETURN = 1;break;
						case 0x2c:KEY_RETURN = 2;break;
						case 0x34:KEY_RETURN = 3;break;
						case 0x38:KEY_RETURN = 4;break;
					}
					KEY_STATE = 2;
				}
			}
			else {
				KEY_STATE = 0;
			}break;
		case 2:
			if(KEY_COUNT == 0x3c) {
				KEY_STATE = 0;
			}break;
	}
	return KEY_RETURN;
}







