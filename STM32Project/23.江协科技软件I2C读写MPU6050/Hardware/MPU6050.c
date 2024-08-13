#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"
#include "MyI2C.h"

#include "MPU6050_Reg.h"

#define MPU6050ADDRESS      0xD0




/**
  * ��    ����ָ����ַдһ���ֽ�
  * ��    ����RegAddress   ָ���ļĴ�����ַ
              Data         ָ��д�������
  * �� �� ֵ����
  */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
    MyI2C_Start();//��ʼ
    MyI2C_SendByte(MPU6050ADDRESS);//ָ���豸��ַ��д����
    MyI2C_ReceiveAck();//����Ӧ��λ
    MyI2C_SendByte(RegAddress);//ָ���Ĵ�����ַ
    MyI2C_ReceiveAck();//����Ӧ��λ
    MyI2C_SendByte(Data);//ָ��д��ָ��������
    MyI2C_ReceiveAck();//����Ӧ��λ
    MyI2C_Stop();//ֹͣ
}

/**
  * ��    ����ָ����ַ��һ���ֽ�
  * ��    ����RegAddress   ָ��Ҫ���ļĴ�����ַ
  * �� �� ֵ����
  */
uint8_t MPU6050_ReadeReg(uint8_t RegAddress)
{
    uint8_t Data = 0x00;
    
    MyI2C_Start();//��ʼ
    MyI2C_SendByte(MPU6050ADDRESS);//ָ���豸��ַ��д����
    MyI2C_ReceiveAck();//����Ӧ��λ
    MyI2C_SendByte(RegAddress);//ָ���Ĵ�����ַ
    MyI2C_ReceiveAck();//����Ӧ��λ
    
    MyI2C_Start();//�ظ���ʼ
    MyI2C_SendByte(MPU6050ADDRESS | 0x01);//ָ���豸��ַ �� ������
    MyI2C_ReceiveAck();//����Ӧ��λ
    Data = MyI2C_ReceiveByte();//���մӻ����͵��ֽ�
    MyI2C_SenndAck(1);//��������Ӧ��λ��Ӧ����������
    MyI2C_Stop();//ֹͣ
    return Data;//���ض�ȡ����ֵ
}

/**
  * ��    ������ʼ��MPU6050
  * ��    ������
  * �� �� ֵ����
  */
void MPU6050_Init(void)
{
    /*��ʼ��I2C*/
    MyI2C_Init();
    /*��ʼ��MPU6050*/
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);  //��Դ����1������λ�����˯�ߡ���ѭ�����¶ȴ�������ʧ�ܡ�ѡ��X��������ʱ��
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);  //��Դ����2������Ҫѭ��ģʽ����Ƶ�ʡ�ÿ���ᶼ����Ҫ����
    
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);  //�����ʷ�Ƶ����������Ŀ�����ԽС���Խ��.�����10��Ƶ
    MPU6050_WriteReg(MPU6050_CONFIG,0x06);  //���üĴ������ⲿͬ������Ҫ�����ֵ�ͨ�˲�������Ϊ110
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);   //���������üĴ��������Բ⡢������ѡ��11�������
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);    //���ٶȼ����üĴ��������Բ⡢������ѡ��11������̡����ø�ͨ�˲���
}


/**
  * ��    �����õ����ᴫ�����е�����
  * ��    ����Str   MPU6050_Data�ĵ�ַ
  * �� �� ֵ����
  */
SensorData MPU6050_Data;
void MPU6050_GetData(SensorData *Str)//������ֽṹ�����͵ĵ�ַ
{
    Str->AccX = ( MPU6050_ReadeReg(MPU6050_ACCEL_XOUT_H) <<8|
                  MPU6050_ReadeReg(MPU6050_ACCEL_XOUT_L));
    Str->AccY = ( MPU6050_ReadeReg(MPU6050_ACCEL_YOUT_H) <<8|
                  MPU6050_ReadeReg(MPU6050_ACCEL_YOUT_L));
    Str->AccZ = ( MPU6050_ReadeReg(MPU6050_ACCEL_ZOUT_H) <<8|
                  MPU6050_ReadeReg(MPU6050_ACCEL_ZOUT_L));
    Str->Temp = ( MPU6050_ReadeReg(MPU6050_TEMP_OUT_H)   <<8|
                  MPU6050_ReadeReg(MPU6050_TEMP_OUT_L));
    Str->GyroX = ( MPU6050_ReadeReg(MPU6050_GYRO_XOUT_H) <<8 |
                  MPU6050_ReadeReg(MPU6050_GYRO_XOUT_L));
    Str->GyroY = ( MPU6050_ReadeReg(MPU6050_GYRO_YOUT_H) <<8 |
                  MPU6050_ReadeReg(MPU6050_GYRO_YOUT_L));
    Str->GyroZ = ( MPU6050_ReadeReg(MPU6050_GYRO_ZOUT_H) <<8 |
                   MPU6050_ReadeReg(MPU6050_GYRO_ZOUT_L));
}
//MPU6050_ACCEL_XOUT_H    0x3B
//MPU6050_ACCEL_XOUT_L    0x3C
//MPU6050_ACCEL_YOUT_H    0x3D
//MPU6050_ACCEL_YOUT_L    0x3E
//MPU6050_ACCEL_ZOUT_H    0x3F
//MPU6050_ACCEL_ZOUT_L    0x40
//MPU6050_TEMP_OUT_H      0x41
//MPU6050_TEMP_OUT_L      0x42
//MPU6050_GYRO_XOUT_H     0x43
//MPU6050_GYRO_XOUT_L     0x44
//MPU6050_GYRO_YOUT_H     0x45
//MPU6050_GYRO_YOUT_L     0x46
//MPU6050_GYRO_ZOUT_H     0x47
//MPU6050_GYRO_ZOUT_L     0x48
