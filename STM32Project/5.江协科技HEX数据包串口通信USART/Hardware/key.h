#ifndef __KEY_H
#define  __KEY_H

#include "stm32f10x.h"
#include "Delay.h"

//�͵�ƽ��Ч����ȡ���͵�ƽ����1
#define KEY1 (!(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) ))//��ȡ GPIOB 11���ŵĺ�
#define KEY2 (!(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)  ))//��ȡ GPIOB 11���ŵĺ�

//��ʼ��KEY����
void KEY_Init(void);

//����ɨ��  1Ϊ֧����������0Ϊ��֧��
uint8_t KEY_Scan(uint8_t mode);


#endif
