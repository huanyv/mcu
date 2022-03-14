#include"stm32f10x.h"
#include"delay.h"

void User_USART_Init() {
	GPIO_InitTypeDef   GPIO_InitStructure;  //����IO�ڳ�ʼ���ṹ��
	USART_InitTypeDef  USART_InitStructure;//���崮�ڳ�ʼ���ṹ��
	NVIC_InitTypeDef   NVIC_InitStructure;  //�����ж����ȼ��ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��ʱ��
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;   //USART1_TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//GPIO���ڷ��ͳ�ʼ��
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;//��������
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;    //USART1_RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//GPIO���ڽ��ճ�ʼ��
	
	USART_InitStructure.USART_BaudRate             = 115200;                             //115200������
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;     //��Ӳ������������
	USART_InitStructure.USART_Mode                 = USART_Mode_Rx | USART_Mode_Tx;      //���ͺͽ���ģʽ�� ��
	USART_InitStructure.USART_Parity               = USART_Parity_No;                    //����żУ��λ
	USART_InitStructure.USART_StopBits             = USART_StopBits_1;                   //ֹͣλ 1
	USART_InitStructure.USART_WordLength           = USART_WordLength_8b;                //�ֳ�Ϊ 8 bit
	USART_Init(USART1,&USART_InitStructure);//���ڳ�ʼ��
	
	NVIC_InitStructure.NVIC_IRQChannel                    = USART1_IRQn;//����ж�ͨ��  stm32f10x.h
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;//ʹ���ж� 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;//�����ȼ�
	NVIC_Init(&NVIC_InitStructure);//�ж����ȼ���ʼ��
	
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//���ж�    ���ջ������ǿ�   �ж�
	
	USART_Cmd(USART1,ENABLE);//ʹ�ܴ���
}

void USART1_IRQHandler() {
	uint8_t temp = 0;//���ձ���
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == 1) {//��� USART1 �жϷ������ڷ�  �����жϺ���ֵΪ  1
		temp = USART_ReceiveData(USART1);//���ݽ���
		USART_SendData(USART1,temp);//���ݷ���
	}
}

int main(void) {
	User_USART_Init();//�Զ����ڳ�ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�ж����������   2λ��ռ  2λ��Ӧ
	while(1);
}





