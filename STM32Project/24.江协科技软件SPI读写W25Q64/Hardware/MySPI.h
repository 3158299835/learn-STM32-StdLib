#ifndef __MYSPI_H
#define __MYSPI_H

//��ʼ��
void MySPI_Init(void);
//��ʼ
void MySPI_Start(void);
//��ֹ
void MySPI_Stop(void);
//����
uint8_t MySPI_WarpByte(uint8_t SendByte);

#endif
