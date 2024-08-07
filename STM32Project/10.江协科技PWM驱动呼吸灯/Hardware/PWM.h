#ifndef __PWM_H
#define __PWM_H

//初始化
void PWM_Init(void);

//修改占空比（CCR的值）
void PWM_SetCompare1(uint16_t Comparel);

#endif
