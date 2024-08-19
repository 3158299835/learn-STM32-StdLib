#ifndef __SERIAL_H 

#include "stm32f10x.h"
#include "stdio.h"
#include "stdarg.h"

#define __SERIAL_H 


//��ʼ������
void Serial_Init(void);

//�����ֽ�
void Serial_SendByte(uint16_t Byte);

//��������
void Serial_SendArray(uint8_t* Array,uint16_t len);

//�����ַ���
void Serial_SendString(char* String);

//�����ַ���ʽ������
void Serial_SendNumber(uint32_t Number,uint8_t len);

//��ֲprintf
void Serial_Printf(char *format, ...);

//��ȡ�����RXNE��־λ
uint8_t Serial_GetRxfalg(void);

//��ȡ������ַ�
uint8_t Serial_GetRxData(void);

#endif
