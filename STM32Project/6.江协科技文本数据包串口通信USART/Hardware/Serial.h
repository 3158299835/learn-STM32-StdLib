#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>


//���������Ľ�������
extern char Serial_RxPacket[];

//��ʼ�����ݰ�����
void Serial_Init(void);

//����һ���ֽ�
void Serial_SendByte(uint8_t Byte);

//����һ������
void Serial_SendArray(uint8_t *Array, uint16_t Length);

//����һ���ַ���
void Serial_SendString(char *String);

//����һ������
void Serial_SendNumber(uint32_t Number, uint8_t Length);

//��ֲprintf
void Serial_Printf(char *format, ...);

//�ж��Ƿ��յ����ݰ��ı�־λ
uint8_t Serial_GetRxFlag(void);

#endif
