#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x_it.h"

// ��ʼ����ʱ����
void Delay_Init(void);

// ΢�뼶��ʱ����
void Delay_us(uint32_t us);

// ���뼶��ʱ����
void Delay_ms(uint32_t ms);



#endif
