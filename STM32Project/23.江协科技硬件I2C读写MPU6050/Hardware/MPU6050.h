#ifndef __MPU6050_H
#define __MPU6050_H

/**
  * ��    ������ʼ��MPU6050
  * ��    ������
  * �� �� ֵ����
  */
void MPU6050_Init(void);

/**
  * ��    ����ָ����ַдһ���ֽ�
  * ��    ����RegAddress   ָ���ļĴ�����ַ
              Data         ָ��д�������
  * �� �� ֵ����
  */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);
/**
  * ��    ����ָ����ַ��һ���ֽ�
  * ��    ����RegAddress   ָ��Ҫ���ļĴ�����ַ
  * �� �� ֵ����
  */
uint8_t MPU6050_ReadeReg(uint8_t RegAddress);


//����������
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
  * ��    �����õ����ᴫ�����е�����
  * ��    ����Str   MPU6050_Data�ĵ�ַ
  * �� �� ֵ����
  */
void MPU6050_GetData(SensorData *Str);

#endif
