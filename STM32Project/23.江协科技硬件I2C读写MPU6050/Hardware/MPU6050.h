#ifndef __MPU6050_H
#define __MPU6050_H

/**
  * 函    数：初始化MPU6050
  * 参    数：无
  * 返 回 值：无
  */
void MPU6050_Init(void);

/**
  * 函    数：指定地址写一个字节
  * 参    数：RegAddress   指定的寄存器地址
              Data         指定写入的数据
  * 返 回 值：无
  */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);
/**
  * 函    数：指定地址读一个字节
  * 参    数：RegAddress   指定要读的寄存器地址
  * 返 回 值：无
  */
uint8_t MPU6050_ReadeReg(uint8_t RegAddress);


//传感器数据
typedef struct Data 
{
    int16_t AccX;
    int16_t AccY;
    int16_t AccZ;
    int16_t Temp;
    int16_t GyroX;
    int16_t GyroY;
    int16_t GyroZ;
}SensorData;

extern SensorData MPU6050_Data;

/**
  * 函    数：得到六轴传感器中的数据
  * 参    数：Str   MPU6050_Data的地址
  * 返 回 值：无
  */
void MPU6050_GetData(SensorData *Str);

#endif
