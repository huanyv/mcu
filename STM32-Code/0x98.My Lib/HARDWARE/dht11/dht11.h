#ifndef __DHT11_H
#define __DHT11_H

#include "sys.h"

#define     DHT11_IO             PAout(0)
#define     DHT11_IO_IN          PAin(0)
#define     DHT11_PIN            GPIO_Pin_0

#define     DHT11_Init()         RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE)


typedef struct
{
	uint8_t RH; // ʪ������
	uint8_t RL; // ʪ��С��
	uint8_t TH; // �¶�����
	uint8_t TL; // �¶�С��
	uint8_t HUM[7]; // ʪ���ַ���
	uint8_t TEMP[7];// �¶��ַ���
}Temperature_AND_Humidity;



void Receive_DATA(Temperature_AND_Humidity *Temperature_AND_humidity_Structure);


#endif /* __DHT11_H */




