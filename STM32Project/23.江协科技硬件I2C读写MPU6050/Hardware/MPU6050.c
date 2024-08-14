#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"
#include "MPU6050_Reg.h"

#define MPU6050ADDRESS      0xD0


/**
  * 函    数：超时退出、检测标志位
  * 参    数：I2C_TypeDef* I2Cx,    定时器x
              uint32_t I2C_EVENT    标志位名称
  * 返 回 值：无
  * 注意事项：无
  */
void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)//超时退出、检测标志位
{
    uint32_t Timeout;
    Timeout = 10000;
    while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)
    {
        Timeout --;
        if (Timeout == 0)
        {
            break;  
        }
    }
}


/**
  * 函    数：指定地址写一个字节
  * 参    数：RegAddress   指定的寄存器地址
              Data         指定写入的数据
  * 返 回 值：无
  */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{

    I2C_GenerateSTART(I2C2,ENABLE);//非阻塞。所以要等待事件发送完成。
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);//等待EV5事件发生

    I2C_Send7bitAddress(I2C2,MPU6050ADDRESS,I2C_Direction_Transmitter);//发送地址和读写操作（也能用发送一个字节来完成）(自动应答)
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);//等待发送EV6事件发生

    I2C_SendData(I2C2,RegAddress);

    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING);//等待发送EV8事件发生(字节正在发送)
    
    I2C_SendData(I2C2,Data);//直接写入下一个要发的数据
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED );//等待EV8_2事件发生(发送完成，并且数据寄存器无)
    
    I2C_GenerateSTOP(I2C2,ENABLE);
}

/**
  * 函    数：指定地址读一个字节
  * 参    数：RegAddress   指定要读的寄存器地址
  * 返 回 值：无
  */
uint8_t MPU6050_ReadeReg(uint8_t RegAddress)
{
    uint8_t Data = 0x00;

    I2C_GenerateSTART(I2C2,ENABLE);//起始位
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);//等待EV5事件发生

    I2C_Send7bitAddress(I2C2,MPU6050ADDRESS,I2C_Direction_Transmitter);//发送地址和读写操作（也能用发送一个字节来完成）(自动应答)
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);//等待发送EV6事件发生

    I2C_SendData(I2C2,RegAddress);
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED);//等待发送EVEV8_2事件发生(字节发送完毕)

    I2C_GenerateSTART(I2C2,ENABLE);//重复起始
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);//等待EV5事件发生
   
    I2C_Send7bitAddress(I2C2,MPU6050ADDRESS,I2C_Direction_Receiver);//发送地址和读写操作（也能用发送一个字节来完成）(自动应答)
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);//等待发送EV6事件发生
  
    I2C_AcknowledgeConfig(I2C2,DISABLE);//在字节来之前，设置非应答。
    I2C_GenerateSTOP(I2C2,ENABLE);//直接停止。但是会接收字节完毕之后才停

    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED);//等待EV7事件到达。代表一个数据的字节已经在DR里了
    Data = I2C_ReceiveData(I2C2);
    
    I2C_AcknowledgeConfig(I2C2,ENABLE);//恢复默认状态，给从机应答
    
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
//    MyI2C_Init();
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启GPIO和I2C外设时钟
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);   //初始化PB10、11为复用开漏
    /*初始化I2C外设*/
    I2C_InitTypeDef I2C_InitStructure;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;//确定是否应答
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//指定STM32作为从机。可以响应几位的地址
    I2C_InitStructure.I2C_ClockSpeed = 50000;//最大400KHZ（快速）、标准为（100KHZ）(MPU6050最快也是400KHZ)
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;//配置占空比。进入快速模式后才有用（>100KHZ后） （默认为1:1）
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;//I2C模式
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;//指定STM32作为从机。STM本身的地址
    I2C_Init(I2C2,&I2C_InitStructure);
    /*使能I2C外设*/
    I2C_Cmd(I2C2,ENABLE);
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
