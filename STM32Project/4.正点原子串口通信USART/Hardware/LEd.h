#ifndef __LED_H //条件编译
#define __LED_H


#include "stm32f10x.h"

//初始化LED
void LED_Init(void);

//点亮LED
void LED_ON(uint8_t num);

//熄灭LED
void LED_OFF(uint8_t num);

//反转LED
void LED_Flip(uint8_t num);
#endif

