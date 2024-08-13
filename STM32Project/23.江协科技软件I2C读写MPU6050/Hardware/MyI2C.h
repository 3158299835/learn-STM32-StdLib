#ifndef __MYI2C_H
#define __MYI2C_H

//��    ������ʼ��I2C
void MyI2C_Init(void);

//��    ������ʼʱ��Ԫ
void MyI2C_Start (void);
    
//��    ��������ʱ��Ԫ
void MyI2C_Stop (void);
    
//��    ��������һ���ֽ�
void MyI2C_SendByte (uint8_t Byte);
    
//��    ��������һ���ֽ�
uint8_t MyI2C_ReceiveByte (void);
    
//��    ��������Ӧ��
void MyI2C_SenndAck (uint8_t AckBit);
    
//��    ��������Ӧ��
uint8_t MyI2C_ReceiveAck (void);







#endif
