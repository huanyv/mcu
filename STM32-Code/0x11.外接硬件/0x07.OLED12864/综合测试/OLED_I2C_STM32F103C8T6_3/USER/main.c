#include "stm32f10x.h"
#include "OLED_I2C.h"
#include "delay.h"
#include "i2c.h"



uint8_t c1[1];//�Զ����ַ�����


int main(void)
{
	unsigned char i;
	extern const unsigned char BMP1[];
	
	GPIO_I2C_Init();
	OLED_Init();	
	OLED_CLS();//���� 
	i = i + 1;i = 0; // ��ʹ�� i ʱʹ��������
	c1[0] = 95+32;
	
#if     0
	
	OLED_DrawBMP(0,0,128,8,(unsigned char *)BMP1);//����BMPλͼ��ʾ
	
	while(1) {
		
	}
	
#elif   1
	
	while(1)
	{
		OLED_Fill(0xFF);//ȫ������
		delay_s(2);
		OLED_Fill(0x00);//ȫ����
		delay_s(2);
		for(i=0;i<6;i++)
		{
			OLED_ShowCN(16+i*16,0,i);//������ʾ����
		}
		delay_s(2);
		OLED_ShowStr(0,3,"HelTec Automation",1);//����6*8�ַ�
		OLED_ShowStr(0,4,"Hello Tech",2);				//����8*16�ַ�
		delay_s(2);
		OLED_CLS();
		OLED_Show12x24(0,0,"0123456789"); //����12*24�ַ�
		OLED_Show16x32(0,3,"ABCDEFGH");   //����16*32�ַ�
		delay_s(2);
		OLED_CLS();//����
		OLED_OFF();//����OLED����
		delay_s(2);
		OLED_ON();//����OLED���ߺ���
		OLED_DrawBMP(0,0,128,8,(unsigned char *)BMP1);//����BMPλͼ��ʾ
		delay_s(2);
	}
	
	
#elif  0
	
	while(1) {
		OLED_ShowStr(0,0,"000000",2);delay_ms(500);  
		OLED_ShowStr(0,0,"000001",2);delay_ms(500);          
		OLED_ShowStr(0,0,"000002",2);delay_ms(500);          
		OLED_ShowStr(0,0,"000003",2);delay_ms(500);          
		OLED_ShowStr(0,0,"000004",2);delay_ms(500);           
		OLED_ShowStr(0,0,"000005",2);delay_ms(500);           
		OLED_ShowStr(0,0,"000006",2);delay_ms(500);          
		OLED_ShowStr(0,0,"000007",2);delay_ms(500); 
	}
	
#elif   0
	
	for(i=0;i<6;i++)
	{
		OLED_ShowCN(16+i*16,2,i);//������ʾ����
	}
	OLED_ShowStr(0,4,  "123456789"  ,2);
	while(1){
		
	}	
#elif   0
	
	
	OLED_ShowStr(0,1,  c1  ,2); // �Զ����ַ�
	OLED_ShowStr(0,4,  "123"  ,2);
	OLED_ShowStr(0,6,  "123"  ,1);
	

	while(1){
		
	}		
	
	
#elif   0
	
	
	OLED_Show16x32(0,0,"12:00:02");
	OLED_Show12x24(0,4,"123456789");
	
	
//	OLED_Show16x32(0,  0,"1");
//	OLED_Show16x32(16, 0,"2");
//	OLED_Show16x32(32, 0,":");
//	OLED_Show16x32(48, 0,"0");
//	OLED_Show16x32(64, 0,"0");
//	OLED_Show16x32(80, 0,":");
//	OLED_Show16x32(96, 0,"0");
//	OLED_Show16x32(112,0,"1");

//	OLED_Show16x32(16, 4 ,"1");
//	OLED_Show16x32(32, 4 ,"6");
//	OLED_Show16x32(48, 4 ,c1);
	
//	OLED_Show16x32(0,  0,"0");
//	OLED_Show16x32(16, 0,"1");
//	OLED_Show16x32(32, 0,"2");
//	OLED_Show16x32(48, 0,"3");
//	OLED_Show16x32(64, 0,"4");
//	OLED_Show16x32(80, 0,"5");
//	OLED_Show16x32(96, 0,"6");
//	OLED_Show16x32(112,0,"7");
//	OLED_Show16x32(0,  4,"8");
//	OLED_Show16x32(16, 4,"9");

//OLED_Show16x32(0,0,"12:00:01");
//OLED_Show16x32(0,4,"ABCDEFGH");



//	OLED_Show12x24(0,0,"0");
//	OLED_Show12x24(12,0,"1");
//	OLED_Show12x24(24,0,"2");
//	OLED_Show12x24(36,0,"3");
//	OLED_Show12x24(48,0,"4");
//	OLED_Show12x24(60,0,"5");
//	OLED_Show12x24(72,0,"6");
//	OLED_Show12x24(84,0,"7");
//	OLED_Show12x24(96,0,"8");
//	OLED_Show12x24(108,0,"9");

//	OLED_Show12x24(0,0,"0123456789AAA");

	while(1){
		
	}	
	
	#endif
}





