#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"
#include "MyI2C.h"

#include "MPU6050_Reg.h"

#define MPU6050ADDRESS      0xD0




/**
  * 函    数：指定地址写一个字节
  * 参    数：RegAddress   指定的寄存器地址
              Data         指定写入的数据
  * 返 回 值：无
  */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
    MyI2C_Start();//起始
    MyI2C_SendByte(MPU6050ADDRESS);//指定设备地址加写操作
    MyI2C_ReceiveAck();//接收应答位
    MyI2C_SendByte(RegAddress);//指定寄存器地址
    MyI2C_ReceiveAck();//接收应答位
    MyI2C_SendByte(Data);//指定写入指定的数据
    MyI2C_ReceiveAck();//接收应答位
    MyI2C_Stop();//停止
}

/**
  * 函    数：指定地址读一个字节
  * 参    数：RegAddress   指定要读的寄存器地址
  * 返 回 值：无
  */
uint8_t MPU6050_ReadeReg(uint8_t RegAddress)
{
    uint8_t Data = 0x00;
    
    MyI2C_Start();//起始
    MyI2C_SendByte(MPU6050ADDRESS);//指定设备地址加写操作
    MyI2C_ReceiveAck();//接收应答位
    MyI2C_SendByte(RegAddress);//指定寄存器地址
    MyI2C_ReceiveAck();//接收应答位
    
    MyI2C_Start();//重复起始
    MyI2C_SendByte(MPU6050ADDRESS | 0x01);//指定设备地址 加 读操作
    MyI2C_ReceiveAck();//接收应答位
    Data = MyI2C_ReceiveByte();//接收从机发送的字节
    MyI2C_SenndAck(1);//主机发送应答位（应答会继续读）
    MyI2C_Stop();//停止
    return Data;//返回读取到的值
}

/**
  * 函    数：初始化MPU6050
  * 参    数：无
  * 返 回 值：无
  */
void MPU6050_Init(void)
{
    /*初始化I2C*/
    MyI2C_Init();
    /*初始化MPU6050*/
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);  //电源管理1：不复位、解除睡眠、不循环、温度传感器不失能、选择X轴陀螺仪时钟
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);  //电源管理2：不需要循环模式唤醒频率、每个轴都不需要待机
    
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);  //采样率分频：数据输出的快慢，越小输出越快.这里给10分频
    MPU6050_WriteReg(MPU6050_CONFIG,0x06);  //配置寄存器：外部同步不需要、数字低通滤波器设置为110
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);   //陀螺仪配置寄存器：不自测、满量程选择：11最大量程
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);    //加速度计配置寄存器：不自测、满量程选择：11最大量程、不用高通滤波器
}


/**
  * 函    数：得到六轴传感器中的数据
  * 参    数：Str   MPU6050_Data的地址
  * 返 回 值：无
  */
SensorData MPU6050_Data;
void MPU6050_GetData(SensorData *Str)//存放这种结构体类型的地址
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
