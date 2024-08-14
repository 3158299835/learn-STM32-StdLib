#include "stm32f10x.h"                  // Device header
#include "MPU6050.h"
#include "MPU6050_Reg.h"

#define MPU6050ADDRESS      0xD0


/**
  * ��    ������ʱ�˳�������־λ
  * ��    ����I2C_TypeDef* I2Cx,    ��ʱ��x
              uint32_t I2C_EVENT    ��־λ����
  * �� �� ֵ����
  * ע�������
  */
void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)//��ʱ�˳�������־λ
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
  * ��    ����ָ����ַдһ���ֽ�
  * ��    ����RegAddress   ָ���ļĴ�����ַ
              Data         ָ��д�������
  * �� �� ֵ����
  */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{

    I2C_GenerateSTART(I2C2,ENABLE);//������������Ҫ�ȴ��¼�������ɡ�
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);//�ȴ�EV5�¼�����

    I2C_Send7bitAddress(I2C2,MPU6050ADDRESS,I2C_Direction_Transmitter);//���͵�ַ�Ͷ�д������Ҳ���÷���һ���ֽ�����ɣ�(�Զ�Ӧ��)
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);//�ȴ�����EV6�¼�����

    I2C_SendData(I2C2,RegAddress);

    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING);//�ȴ�����EV8�¼�����(�ֽ����ڷ���)
    
    I2C_SendData(I2C2,Data);//ֱ��д����һ��Ҫ��������
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED );//�ȴ�EV8_2�¼�����(������ɣ��������ݼĴ�����)
    
    I2C_GenerateSTOP(I2C2,ENABLE);
}

/**
  * ��    ����ָ����ַ��һ���ֽ�
  * ��    ����RegAddress   ָ��Ҫ���ļĴ�����ַ
  * �� �� ֵ����
  */
uint8_t MPU6050_ReadeReg(uint8_t RegAddress)
{
    uint8_t Data = 0x00;

    I2C_GenerateSTART(I2C2,ENABLE);//��ʼλ
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);//�ȴ�EV5�¼�����

    I2C_Send7bitAddress(I2C2,MPU6050ADDRESS,I2C_Direction_Transmitter);//���͵�ַ�Ͷ�д������Ҳ���÷���һ���ֽ�����ɣ�(�Զ�Ӧ��)
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);//�ȴ�����EV6�¼�����

    I2C_SendData(I2C2,RegAddress);
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED);//�ȴ�����EVEV8_2�¼�����(�ֽڷ������)

    I2C_GenerateSTART(I2C2,ENABLE);//�ظ���ʼ
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);//�ȴ�EV5�¼�����
   
    I2C_Send7bitAddress(I2C2,MPU6050ADDRESS,I2C_Direction_Receiver);//���͵�ַ�Ͷ�д������Ҳ���÷���һ���ֽ�����ɣ�(�Զ�Ӧ��)
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);//�ȴ�����EV6�¼�����
  
    I2C_AcknowledgeConfig(I2C2,DISABLE);//���ֽ���֮ǰ�����÷�Ӧ��
    I2C_GenerateSTOP(I2C2,ENABLE);//ֱ��ֹͣ�����ǻ�����ֽ����֮���ͣ

    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED);//�ȴ�EV7�¼��������һ�����ݵ��ֽ��Ѿ���DR����
    Data = I2C_ReceiveData(I2C2);
    
    I2C_AcknowledgeConfig(I2C2,ENABLE);//�ָ�Ĭ��״̬�����ӻ�Ӧ��
    
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
//    MyI2C_Init();
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//����GPIO��I2C����ʱ��
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);   //��ʼ��PB10��11Ϊ���ÿ�©
    /*��ʼ��I2C����*/
    I2C_InitTypeDef I2C_InitStructure;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;//ȷ���Ƿ�Ӧ��
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//ָ��STM32��Ϊ�ӻ���������Ӧ��λ�ĵ�ַ
    I2C_InitStructure.I2C_ClockSpeed = 50000;//���400KHZ�����٣�����׼Ϊ��100KHZ��(MPU6050���Ҳ��400KHZ)
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;//����ռ�ձȡ��������ģʽ������ã�>100KHZ�� ��Ĭ��Ϊ1:1��
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;//I2Cģʽ
    I2C_InitStructure.I2C_OwnAddress1 = 0x00;//ָ��STM32��Ϊ�ӻ���STM����ĵ�ַ
    I2C_Init(I2C2,&I2C_InitStructure);
    /*ʹ��I2C����*/
    I2C_Cmd(I2C2,ENABLE);
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
