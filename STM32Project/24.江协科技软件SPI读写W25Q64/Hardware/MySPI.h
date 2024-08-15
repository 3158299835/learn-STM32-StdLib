#ifndef __MYSPI_H
#define __MYSPI_H

//初始化
void MySPI_Init(void);
//起始
void MySPI_Start(void);
//终止
void MySPI_Stop(void);
//交换
uint8_t MySPI_WarpByte(uint8_t SendByte);

#endif
