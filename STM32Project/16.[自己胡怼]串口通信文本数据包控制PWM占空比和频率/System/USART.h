#ifndef __USART_H
#define __USART_H

//��ʼ��
void USART1_Init(void);
//�����ַ�
void USART1_SendStr(char Data);
//�����ַ���
void USART1_SendString(char* Data);
//��ȡ�����ַ����ı�־λ
uint8_t USART1_GetRxFlag(void);
#endif
