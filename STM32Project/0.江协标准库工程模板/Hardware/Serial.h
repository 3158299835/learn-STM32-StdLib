#ifndef __SERIAL_H 

#include "stm32f10x.h"
#include "stdio.h"
#include "stdarg.h"

#define __SERIAL_H 


//初始化串口
void Serial_Init(void);

//发送字节
void Serial_SendByte(uint16_t Byte);

//发送数组
void Serial_SendArray(uint8_t* Array,uint16_t len);

//发送字符串
void Serial_SendString(char* String);

//发送字符形式的数字
void Serial_SendNumber(uint32_t Number,uint8_t len);

//移植printf
void Serial_Printf(char *format, ...);

//获取输入的RXNE标志位
uint8_t Serial_GetRxfalg(void);

//获取输入的字符
uint8_t Serial_GetRxData(void);

#endif
