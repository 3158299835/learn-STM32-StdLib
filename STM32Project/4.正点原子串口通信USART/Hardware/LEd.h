#ifndef __LED_H //��������
#define __LED_H


#include "stm32f10x.h"

//��ʼ��LED
void LED_Init(void);

//����LED
void LED_ON(uint8_t num);

//Ϩ��LED
void LED_OFF(uint8_t num);

//��תLED
void LED_Flip(uint8_t num);
#endif

