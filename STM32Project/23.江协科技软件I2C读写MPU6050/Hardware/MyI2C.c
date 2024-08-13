#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define SCL_Clock   RCC_APB2Periph_GPIOA
#define SCL_PORT    GPIOA
#define SCL_Pin     GPIO_Pin_11

#define SDA_Clock   RCC_APB2Periph_GPIOA
#define SDA_PORT    GPIOA
#define SDA_Pin     GPIO_Pin_12


/**
  * ��    ������ʼ��I2C
  * ��    ������
  * �� �� ֵ����
  */
void MyI2C_Init(void)
{
    Delay_Init();//��ʼ����ʱ����
    
    /*����SCL��SDAʱ��*/
    RCC_APB2PeriphClockCmd(SCL_Clock,ENABLE);
    RCC_APB2PeriphClockCmd(SDA_Clock,ENABLE);
    
    /*��ʼ��SCL��SDA����*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_InitStructure.GPIO_Pin = SCL_Pin;
    GPIO_Init(SCL_PORT,&GPIO_InitStructure);   //SCL����Ϊ��©���
    
    GPIO_InitStructure.GPIO_Pin = SDA_Pin;
    GPIO_Init(SDA_PORT,&GPIO_InitStructure);   //SDA����Ϊ��©���
    
    GPIO_SetBits(SCL_PORT,SCL_Pin);//����SCL
    GPIO_SetBits(SDA_PORT,SDA_Pin);//����SDA
}

/**
  * ��    ����дһλSCL
  * ��    ����0��1
  * �� �� ֵ����
  */
void MyI2C_W_SCL (uint8_t BitValue)
{
    GPIO_WriteBit(SCL_PORT,SCL_Pin,(BitAction)BitValue);//BitAction��һ��typedef��ö������ֵ��
    Delay_us(10);   //��ʱ�����ӻ���ȡʱ��
}

/**
  * ��    ����дһλSDA
  * ��    ����0��1
  * �� �� ֵ����
  */
void MyI2C_W_SDA (uint8_t BitValue)
{
    GPIO_WriteBit(SDA_PORT,SDA_Pin,(BitAction)BitValue);
    Delay_us(10);   //��ʱ�����ӻ���ȡʱ��
}

/**
  * ��    ������һλSDA
  * ��    ������
  * �� �� ֵ��BitValue
  */
uint8_t MyI2C_R_SDA (void)
{
    uint8_t BitValue = 0x00;   
    BitValue = GPIO_ReadInputDataBit(SDA_PORT,SDA_Pin);
    Delay_us(10);
    return BitValue;
}

/**
  * ��    ������ʼʱ��Ԫ
  * ��    ������
  * �� �� ֵ����
  */
void MyI2C_Start (void)
{
    MyI2C_W_SDA(1);
    MyI2C_W_SCL(1);//������SDA������SCL���ߡ���ֹ���ظ���ʼʱ������ֹ����
    MyI2C_W_SDA(0);
    MyI2C_W_SCL(0);//��SDA���ͣ���SCL���͡�������ʼ����
}

/**
  * ��    ��������ʱ��Ԫ
  * ��    ������
  * �� �� ֵ����
  */
void MyI2C_Stop (void)
{
    MyI2C_W_SDA(0);//��SCLΪ�͵�ƽʱ���Ȱ�SDA���ߣ�Ϊ������׼��
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(1);//��SCL���ߣ���SDA���ߡ�������������
}

/**
  * ��    ��������һ���ֽ�
  * ��    ����Byte
  * �� �� ֵ����
  */
void MyI2C_SendByte (uint8_t Byte)
{
    uint8_t i = 0;
    for(i = 0; i < 8; i++)
    {
        MyI2C_W_SDA( Byte & (0x80 >> i) );//�������λ��������ȡ��bitд��
        MyI2C_W_SCL(1);//�ӻ���ȡ
        MyI2C_W_SCL(0);//׼���´�д��
    }
}

/**
  * ��    ��������һ���ֽ�
  * ��    ������
  * �� �� ֵ��Byte
  */
uint8_t MyI2C_ReceiveByte (void)
{
    MyI2C_W_SDA(1);//�ͷ�SDA����
    uint8_t Byte = 0x00;//��ŵõ���bit
    
    uint8_t i = 0;
    for(i = 0; i < 8; i++)
    {
        MyI2C_W_SCL(1);//����׼����ȡ
        if (MyI2C_R_SDA() == 1)//�����������һλΪ1
        {
            Byte |= (0x80 >> i);//�Ͱ���һλ��1������Ĭ��Ϊ0
        }
        MyI2C_W_SCL(0);//�ӻ�����һλbit������
    }
    return Byte;
}

/**
  * ��    ��������Ӧ��
  * ��    ����AckBit
  * �� �� ֵ����
  */
void MyI2C_SenndAck (uint8_t AckBit)
{
    
        MyI2C_W_SDA(AckBit);//Ӧ��
        MyI2C_W_SCL(1);//�ӻ���ȡ
        MyI2C_W_SCL(0);//׼���´ζ���
}

/**
  * ��    ��������Ӧ��
  * ��    ������
  * �� �� ֵ��reply
  */
uint8_t MyI2C_ReceiveAck (void)
{
    MyI2C_W_SDA(1);//�ͷ�SDA����
    uint8_t AckBit = 0x00;//��ŵõ���bit

    MyI2C_W_SCL(1);//�ӻ���д
    AckBit = MyI2C_R_SDA();//������ȡ
    MyI2C_W_SCL(0);//׼���´ζ���
    return AckBit;
}












