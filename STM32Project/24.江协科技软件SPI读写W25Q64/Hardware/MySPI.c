#include "stm32f10x.h"                  // Device header

/*���������б�*/
#define RCCPeriph       RCC_APB2Periph_GPIOA
#define SCK_Port        GPIOA
#define SCK_Pin         GPIO_Pin_6
#define SS_Port         GPIOA
#define SS_Pin          GPIO_Pin_5
#define MOSI_Port       GPIOA
#define MOSI_Pin        GPIO_Pin_4
#define MISO_Port       GPIOA
#define MISO_Pin        GPIO_Pin_3

/**
  * ��    ����дƬѡ�ź�SS
  * ��    ����BitValue������1Ƭѡ�ź�SSΪ�ߵ�ƽ
  * �� �� ֵ����
  * ע�������
  */
void MySPI_W_SS (uint8_t BitValue)
{
    GPIO_WriteBit(SS_Port,SS_Pin,(BitAction)BitValue);
}

/**
  * ��    ����дʱ���ź�SCK
  * ��    ����BitValue������1ʱ���ź�SCKΪ�ߵ�ƽ
  * �� �� ֵ����
  * ע�������
  */
void MySPI_W_SCK (uint8_t BitValue)
{
    GPIO_WriteBit(SCK_Port,SCK_Pin,(BitAction)BitValue);
}

/**
  * ��    ����д ����������ӻ������ź�MOSI
  * ��    ����BitValue������1ʱ��������ߵ�ƽ
  * �� �� ֵ����
  * ע�������
  */
void MySPI_W_MOSI (uint8_t BitValue)
{
    GPIO_WriteBit(MOSI_Port,MOSI_Pin,(BitAction)BitValue);
}

/**
  * ��    ������ �������룬�ӻ�����ź�MISO
  * ��    ������
  * �� �� ֵ��BitValue
  * ע�������
  */
uint8_t MySPI_R_MISO (void)
{
    return GPIO_ReadInputDataBit(MISO_Port,MISO_Pin);
}

/**
  * ��    ����MySPI��ʼ��
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
void MySPI_Init(void)
{   
    /*����ʱ��������*/
    RCC_APB2PeriphClockCmd(RCCPeriph,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = SCK_Pin | SS_Pin | MOSI_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MOSI_Port,&GPIO_InitStructure);   //ʱ�ӡ�Ƭѡ��MOSI�����������
    
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = MISO_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MISO_Port,&GPIO_InitStructure);   //MISO Ϊ��������
    
    MySPI_W_SS(1);  //ƬѡĬ��Ϊ��
    MySPI_W_SCK(0); //ʱ��Ĭ��Ϊ��
}







/*******************/
/*SPI������ʱ��Ԫ*/
/*******************/





/**
  * ��    ������ʼ�ź�
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
void MySPI_Start(void)
{   
    MySPI_W_SS(0);
}

/**
  * ��    ������ֹ����
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
void MySPI_Stop(void)
{   
    MySPI_W_SS(1);
}


/**
  * ��    ��������һ���ֽڣ�ģʽ0��������1��
  * ��    ����SendByte      �����͵��ֽ�
  * �� �� ֵ��ReceiveByte   ���յ����ֽ�
  * ע���������ʹ������������ȡ�����е�ÿһλ�������
              �ô��ǲ���ı䴫�������������Ч�ʲ���
              ���Ҫ��Ϊģʽ1�������������ٷ��͡����½����ٽ��գ�2��3��ֱ�Ӹ�ʱ�Ӽ��Ծ�ok�ˣ�
  */
//uint8_t MySPI_WarpByte(uint8_t SendByte)
//{
//    uint8_t ReceiveByte = 0x00;
//    
//    uint8_t i = 0;
//    for(i = 0; i < 8; i++)
//    {
//        MySPI_W_MOSI(SendByte & (0x80 >> i));  //���͵�һ��bit
//        MySPI_W_SCK(1);//������������
//        if (MySPI_R_MISO() == 1)
//        {
//            ReceiveByte |= (0x80 >> i);    //���մӸ����ͽ�������
//        }
//        MySPI_W_SCK(0); //�½�������
//    }
//    return ReceiveByte;
//} 

/**
  * ��    ��������һ���ֽڣ�ģʽ0��������2��
  * ��    ����SendByte      �����͵��ֽ�
  * �� �� ֵ��ReceiveByte   ���յ����ֽ�
  * ע���������ʹ������λģ�͵ķ�ʽ��Ч�ʸ���
              ���Ҫ��Ϊģʽ1�������������ٷ��͡����½����ٽ��գ�2��3��ֱ�Ӹ�ʱ�Ӽ��Ծ�ok�ˣ�
  */
uint8_t MySPI_WarpByte(uint8_t SendByte)
{
    uint8_t i = 0;
    for(i = 0; i < 8; i++)
    {
        MySPI_W_MOSI(SendByte & 0x80);  //���͵�һ��bit
        SendByte <<= 1; //������������һλ
        MySPI_W_SCK(1); //������������
        if (MySPI_R_MISO() == 1)
        {
            SendByte |= 0x01;    //�����յ������ݵ����ͼĴ��������λ
        }
        MySPI_W_SCK(0); //�½�������
    }
    return SendByte;
} 




