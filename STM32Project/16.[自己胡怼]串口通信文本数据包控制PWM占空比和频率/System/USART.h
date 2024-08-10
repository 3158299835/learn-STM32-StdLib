#ifndef __USART_H
#define __USART_H

//初始化
void USART1_Init(void);
//发送字符
void USART1_SendStr(char Data);
//发送字符串
void USART1_SendString(char* Data);
//获取接收字符串的标志位
uint8_t USART1_GetRxFlag(void);
#endif
