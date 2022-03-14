#ifndef _DHT11_H_
#define _DHT11_H_



#define    uchar         unsigned char
#define    uint          unsigned int
	
#define    SET           1
#define    RESET         0


sbit IO=P3^7;         //Êý¾Ý¿Ú



//void delay_1ms(uint i);
//void start();
//uchar receive_byte();
void receive(int *temp,int *hum);




#endif
