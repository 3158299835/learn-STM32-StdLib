#ifndef __PWM_H
#define __PWM_H

//��ʼ��
void PWM_Init(void);

//�ı�PSC��Ƶ�ʣ�
void PWM_SetPrescaler(uint16_t Prescaler);

//�ı�CCR��ռ�ձȣ�
void PWM_SetCompare1(uint16_t Compare1);

#endif
