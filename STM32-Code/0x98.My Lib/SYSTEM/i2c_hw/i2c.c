#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include <stdio.h>
 
void I2C2_Init(I2C_InitTypeDef* I2C_InitStruct)
{
	GPIO_InitTypeDef GPIO_InitStruct; 
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 	
	
	/* 配置IO管脚 */
	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;   	 
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;   	 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &GPIO_InitStruct); 
   
   	I2C_Init(I2C2, I2C_InitStruct);
	I2C_Cmd(I2C2, ENABLE);
	
	// 配置NVIC
/*	NVIC_InitStructure.NVIC_IRQChannel = I2C2_EV_IRQn   ;				//I2C事件中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级1 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			//子优先级2 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//使能中断通道
	NVIC_Init(&NVIC_InitStructure);  	  						//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 */
 
	//I2C_ITConfig(I2C2, I2C_IT_EVT, ENABLE); //打开事件中断
}

/* i2c 写一个字节*/
/* Byte Write */
void I2C2_WriteByte(uint8_t DeviceAddress, uint8_t MemoryAddress, uint8_t Data)
{
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));   	//等待I2C空闲 
 
	//起始信号
	I2C_GenerateSTART(I2C2, ENABLE);
	while( I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS );  //EV5
	
	//device address//设备地址
	I2C_Send7bitAddress(I2C2, DeviceAddress, I2C_Direction_Transmitter); //写模式    
	while( I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS ); 	//EV6
	//printf("address over\r\n") ; 
 
	//memory address //写内存地址
	I2C_SendData(I2C2, MemoryAddress);  
	while( I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS );  //EV8
			
	//data//发送数据
   	I2C_SendData(I2C2, Data);   
	while( I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS );  //EV8
 
	//stop // 停止信号
	I2C_GenerateSTOP(I2C2, ENABLE); 
}
 
/* i2c 读一个字节*/
/* Random Read */
uint8_t I2C2_ReadByte(uint8_t DeviceAddress, uint8_t MemoryAddress)
{
	uint8_t	Data;
	
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));   	//等待I2C空闲  
	//start  //起始信号
	I2C_GenerateSTART(I2C2, ENABLE);
	while( I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS ); //ev5 
 
	//device address  //设备地址
	I2C_Send7bitAddress(I2C2, DeviceAddress, I2C_Direction_Transmitter);  //写模式
	while( I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS ); 	//ev6 
	 
	//memory address  //内存地址
	I2C_SendData(I2C2,  MemoryAddress);
	while( I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS ) ;   //EV8
																		  
	//start  //二次起始信号
	I2C_GenerateSTART(I2C2, ENABLE);
	while( I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS ) ; //ev5 	
 
	//device address  //设备地址
	I2C_Send7bitAddress(I2C2, DeviceAddress, I2C_Direction_Receiver); //读模式
	while( I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS ) ;  //ev6 
	
	/* 按照manual的图273，先读取数据，关闭ACK应答，最后发出STOP*/   	
	while( I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS );  //EV7	/* 等待读取事件，再读取数据 */
   	Data = I2C_ReceiveData(I2C2); 
        I2C_AcknowledgeConfig(I2C2, DISABLE); //关闭应答和停止条件产生  
	printf("received\r\n");
	I2C_GenerateSTOP(I2C2, ENABLE); 
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);  
 
	return Data;
}