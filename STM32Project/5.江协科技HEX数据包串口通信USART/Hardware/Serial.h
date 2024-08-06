#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>

//对外声明的发送数组
extern uint8_t Serial_TxPacket[];
//对外声明的接收数组
extern uint8_t Serial_RxPacket[];

//初始化数据包串口
void Serial_Init(void);

//发送一个字节
void Serial_SendByte(uint8_t Byte);

//发送一个数组
void Serial_SendArray(uint8_t *Array, uint16_t Length);

//发送一个字符串
void Serial_SendString(char *String);

//发送一个数字
void Serial_SendNumber(uint32_t Number, uint8_t Length);

//移植printf
void Serial_Printf(char *format, ...);

//发送数据包
void Serial_SendPacket(void);

//判断是否收到数据包的标志位
uint8_t Serial_GetRxFlag(void);

#endif
