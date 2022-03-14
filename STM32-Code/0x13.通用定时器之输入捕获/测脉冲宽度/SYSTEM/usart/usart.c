#include "usart.h"

static void USARTx_GPIO_Config(void) {
	GPIO_InitTypeDef  GPIO_InitStructure;  //����IO�ڳ�ʼ���ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;   //USART1_TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//GPIO���ڷ��ͳ�ʼ��
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;//��������
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;    //USART1_RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//GPIO���ڽ��ճ�ʼ��
}
static void USARTx_MODE_Config(void) {
	USART_InitTypeDef  USART_InitStructure;//���崮�ڳ�ʼ���ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ�ܴ���ʱ��
	
	USART_InitStructure.USART_BaudRate             = 115200;                             //115200������
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;     //��Ӳ������������
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;      //���ͺͽ���ģʽ�� ��
	USART_InitStructure.USART_Parity               = USART_Parity_No;                    //����żУ��λ
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;                   //ֹͣλ 1
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;                //�ֳ�Ϊ 8 bit
	USART_Init(USART1,&USART_InitStructure);//���ڳ�ʼ��

#if  USART_ITCONFIG
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//���ж�    ���ջ������ǿ�   �ж�
#endif
	
	USART_Cmd(USART1,ENABLE);//ʹ�ܴ���
}

#if  USART_ITCONFIG
static void USARTx_NVIC_Config(void) {
	NVIC_InitTypeDef  NVIC_InitStructure;  //�����ж����ȼ��ṹ��
	
	NVIC_InitStructure.NVIC_IRQChannel                    = USART1_IRQn;//����ж�ͨ��  stm32f10x.h
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;//ʹ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 2;//�����ȼ�
	NVIC_Init(&NVIC_InitStructure);//�ж����ȼ���ʼ��
}
#endif

void USARTx_Init(void) {
	USARTx_GPIO_Config();
	USARTx_MODE_Config();
	
#if  USART_ITCONFIG
	USARTx_NVIC_Config();
#endif	

}



#if    1

#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}

#else

// ��Ҫ��ħ������ѡ��   Use MicroLIB	  
// ��������
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (unsigned char) ch);// USART1 ���Ի��� USART2 ��
	while (!(USART1->SR & USART_FLAG_TXE));
	return (ch);
}
// ��������
int GetKey (void)  
{
	while (!(USART1->SR & USART_FLAG_RXNE));
	return ((int)(USART1->DR & 0x1FF));
}




#endif











	






