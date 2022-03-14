#include<reg51.h>
#include<intrins.h>
#include <string.h>
#include <stdio.h>
#define uchar unsigned char
#define uint  unsigned int

sbit RS=  P2^0  ;							//Һ����ʾ���Ŷ���
sbit RW=  P2^1  ;
sbit EN=  P2^2  ;
uint  t=0,dian=0;
uchar LCD_LINE_ONE[16]={"tp1:           "};		//������ʾ��Ļ
uchar LCD_LINE_TWO[16]={"tp2:           "};
//uchar LCD_LINE_THR[16]={"                "};

int Tm;
int  fushu=0 ;
sbit DQ= P3^3;										   
static unsigned char get_serial[]={		  //��ȡ�İ˸�DS18B20�ڲ�RAM64λ���к�
   224, 0,0,0,  184,  197, 50, 40,
   215, 0,0,0,  184,  197, 51, 40
  //  82, 0,0,0,  184,  197, 52, 40
 // 101, 0,0,0,  184,  197,  53,40,
  //60, 0,0,0,  184,  197,  54,40,
   //11, 0,0,0,  184,  197,  55,40,
    //47, 0,0,0,  184,  197,  56,40,
	 //185, 0,0,0,  184,  197,  49,40,
 };
void delay( ms )					  //����Һ����ʾ����ʱ����
{
	  int i ;
	  while(ms--)
	  {
	       for(i=0 ;i<5 ;i++ )  ;

	  }
}

uchar Read_LCD_State()				  //��ȡҺ����ʾ��״̬
{
 	uchar state;
	RS=0;RW=1;EN=1;delay(1);
	state=P0;
	EN = 0;delay(1);
	return state;
}
void LCD_Busy_Wait()				 //���æ��ȴ�����
{
 	while((Read_LCD_State()&0x80)==0x80);
	delay(5);
}

void Write_LCD_Zhilin(uchar zl)			  //Һ����ʾдָ���
{
	LCD_Busy_Wait();
	RS=0;RW=0;
	EN=0;
	P0=zl;
	EN=1;
	delay(1);
	EN=0;	
}
void Write_LCD_shuju(uchar date)	     //Һ����ʾд���ݺ���
{
 	LCD_Busy_Wait();
	RS=1;RW=0;
	EN=0;
	P0=date;
	EN=1;
	delay(1);
	EN=0;	
}
 void LCD_INIT()				//Һ����ʾ��ʼ��
{
    Write_LCD_Zhilin(0x38);	  // ��ʾģʽ����
	delay(1);				  
	Write_LCD_Zhilin(0x01);	  // ��ʾ����
	delay(1);				 
	Write_LCD_Zhilin(0x06);	  // ����ƶ�����
	delay(1);
	Write_LCD_Zhilin(0x0c);	  // �����������
	delay(1);
}
 void Display_LCD_String(uchar p,uchar *s)		  //Һ����ʾд�뺯��
{
 	uchar i;
	Write_LCD_Zhilin(p|0x80)	;    //д��ַ��λΪһ
	//Write_LCD_Zhilin(0x40|0x80);
	for(i=0;i<16;i++)
	{
		Write_LCD_shuju(s[i]);
		delay(1); 	
	}
}
/***************************************************************************************/
void delays(int us)					   //����DS18B20����ʱ����
{ int s;
for ( s=0; s<us; s++);
}
void rst(void)						//DS18B20��ʼ��
{
DQ = 1;
delays(2);
DQ = 0;
delays(30); //��ȷ��ʱ 480~960us
DQ = 1;
delays(8);
}
void write(unsigned char ku)		//DS18B20д����
{
int i=0;
     for (i=0;i<8;i++)
    {
		DQ=0;
		DQ =ku&0x01;
		delays(3);
		DQ=1;
		ku>>=1;
    }
}
void match_rom(unsigned char *rom)	  //DS18B20ƥ��ROM����
{
 unsigned char i;
 rst();							  //��ʼ��
 write(0x55);					  //ƥ��ROM
 for(i=8;i>0;i--)
 {
    write(*(rom+i-1));
 }
}
unsigned int read(void)			  //DS18B20��������ÿ�ζ�16λ
{
	int i=0;
	unsigned int u=0;
    for (i=0;i<16;i++)
    {
		DQ=0;
		u>>=1;
		DQ=1;
		if(DQ) u|=0x8000;
		delays(4);
     }
    return (u);
}
int  read0(unsigned char *seria)	//��ȡ��Ӧ�¶�ֵ��ת������
{
  int temperature ;
  unsigned int tp;
  unsigned int lsb;
  rst();				//��ʼ��
  write(0xCC);	//����RAM
	write(0x44);		//�¶�ת��
	rst();				  //�ٴγ�ʼ��
	write(0xCC); 
	match_rom(seria);    //ƥ��ROM��������
	 	write(0xBE);	 //��ȡ�洢��ָ��
	tp=read();			 //��ȡ�¶�ֵ
	if((tp&0xf800)==0xf800)		//�ж�������
	    {
		     fushu=1 ;
	  	    tp=~tp+1 ;
	    	lsb=(unsigned int)(tp*6.25); 
			dian=lsb%100;		  //ȡС������
		
	     	temperature=lsb/100;

		}
     else
	    {
		    fushu=0;
		    lsb=(unsigned int)(tp*6.25); 
			dian=lsb%100;  
		
	     	temperature=lsb/100;

    	 } 
     return(temperature);
}
/*****************************************************************************************/
void main()
{
      uint i ;
	  LCD_INIT();
	  EA=0 ;		 //ʹ��DS18B20��ֹ�κ��ж�
	  while(1)
	 {	  
	      for(i=0;i<2;i++)
		  {	
		      Tm=read0(get_serial+i*8);
				if(i==0)				   //�ж��ǵڼ���������
				{
					   if(fushu==0)					   //�ж��Ƿ�Ӹ���
					        sprintf(LCD_LINE_ONE+5," %d", Tm); 
					   if(fushu==1)
						    sprintf(LCD_LINE_ONE+5,"-%d", Tm); 
				       sprintf(LCD_LINE_ONE+10,".%d",dian);		//����С������
					   Display_LCD_String(0x00,LCD_LINE_ONE);
				 }
				if(i==1)
				{  
				       if(fushu==0)	
					         sprintf(LCD_LINE_TWO+5," %d", Tm); 
					   if(fushu==1)
						     sprintf(LCD_LINE_TWO+5,"-%d", Tm); 
				       sprintf(LCD_LINE_TWO+10,".%d",dian);
					   Display_LCD_String(0x40,LCD_LINE_TWO); 
				}

		  }

		
	 }
}














