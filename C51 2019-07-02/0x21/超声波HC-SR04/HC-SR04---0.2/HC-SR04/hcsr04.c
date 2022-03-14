#include "reg52.h"
#include "hcsr04.h"
#include "intrins.h"

#define Sound_Speed    0.034624//25 C
//#define Sound_Speed    0.034566//24 C
//#define Sound_Speed    0.034508//23 C
//#define Sound_Speed    0.034449//22 C
//#define Sound_Speed    0.034491//21 C
//#define Sound_Speed    0.034432//20 C





void HC_SR04Start(void) {
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
uint HC_SR04EchoTime(void) {
    uint time = 0;
    uint tt = 0;//±ÜÃâËÀÑ­»·±äÁ¿
    TH0 = 0x00;
    TL0 = 0x00;

    tt = 65535;
    while((ECHO == 0)&&(tt>=10)) {
        tt--;
				_nop_();
    }
    if(tt>=10) {
        TR0 = 1;

        tt = 65535;
        while((ECHO == 1)&&(tt>=10)) {
            tt--;
						_nop_();
        }
        if(tt>=10) {
            TR0 = 0;

            time = TH0;
            time <<= 8;
            time |= TL0;
        }
    }
    return time;
}
uint HC_SR04EchoDistance(void) {
    uint    time;
    uint    distance;
    HC_SR04Start();
    time = HC_SR04EchoTime();
    distance = (((double)time*Sound_Speed)/2.0)*10+0.5;
    return distance;
}
