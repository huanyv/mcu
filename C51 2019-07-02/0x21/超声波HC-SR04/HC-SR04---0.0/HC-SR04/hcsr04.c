#include "reg52.h"
#include "hcsr04.h"
#include "intrins.h"

void HC_SR04Status(void) {
    TRIG = 0;
    TRIG = 1;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    TRIG = 0;
}
int HC_SR04EchoTime(void) {
    int time = 0;
		TH0 = 0x00;
		TL0 = 0x00;
    while(!ECHO);
    TR0 = 1;
    while(ECHO);
    TR0 = 0;
    time = TH0;
    time <<= 8;
    time |= TL0;


    return time;
}
uint HC_SR04EchoDistance(void) {
    uint time;
    uint distance;
    HC_SR04Status();
    time = HC_SR04EchoTime();
    distance = (((double)time*0.034624)/2.0)*10+0.5;//25
//		distance = (((double)time*0.034566)/2.0)*10+0.5;//24
//		distance = (((double)time*0.034508)/2.0)*10+0.5;//23
//		distance = (((double)time*0.034449)/2.0)*10+0.5;//22
//		distance = (((double)time*0.034491)/2.0)*10+0.5;//21
//		distance = (((double)time*0.034432)/2.0)*10+0.5;//20
    return distance;
}
