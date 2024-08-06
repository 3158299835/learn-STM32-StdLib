#ifndef __KEY_H
#define  __KEY_H

#include "stm32f10x.h"
#include "Delay.h"

//低电平有效，读取到低电平返回1
#define KEY1 (!(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) ))//读取 GPIOB 11引脚的宏
#define KEY2 (!(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)  ))//读取 GPIOB 11引脚的宏

//初始化KEY引脚
void KEY_Init(void);

//按键扫描  1为支持连续按，0为不支持
uint8_t KEY_Scan(uint8_t mode);


#endif
