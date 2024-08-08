#ifndef __PWM_H
#define __PWM_H

//初始化
void PWM_Init(void);

//改变PSC（频率）
void PWM_SetPrescaler(uint16_t Prescaler);

//改变CCR（占空比）
void PWM_SetCompare1(uint16_t Compare1);

#endif
