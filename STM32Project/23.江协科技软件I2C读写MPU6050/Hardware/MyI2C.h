#ifndef __MYI2C_H
#define __MYI2C_H

//函    数：初始化I2C
void MyI2C_Init(void);

//函    数：起始时序单元
void MyI2C_Start (void);
    
//函    数：结束时序单元
void MyI2C_Stop (void);
    
//函    数：发送一个字节
void MyI2C_SendByte (uint8_t Byte);
    
//函    数：接收一个字节
uint8_t MyI2C_ReceiveByte (void);
    
//函    数：发送应答
void MyI2C_SenndAck (uint8_t AckBit);
    
//函    数：接收应答
uint8_t MyI2C_ReceiveAck (void);







#endif
