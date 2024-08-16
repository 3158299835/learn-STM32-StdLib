#include "stm32f10x.h"                  // Device header

/*���������б�*/
#define RCC_GPIO        RCC_APB2Periph_GPIOA
#define RCC_SPI1        RCC_APB2Periph_SPI1
#define SCK_Port        GPIOA
#define SCK_Pin         GPIO_Pin_5
#define SS_Port         GPIOA
#define SS_Pin          GPIO_Pin_4
#define MOSI_Port       GPIOA
#define MOSI_Pin        GPIO_Pin_7
#define MISO_Port       GPIOA
#define MISO_Pin        GPIO_Pin_6

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
  * ��    ����MySPI��ʼ��
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
void MySPI_Init(void)
{   
    /*����SPI��GPIO����ʱ��*/
    RCC_APB2PeriphClockCmd(RCC_SPI1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_GPIO,ENABLE);
    /*��������*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = SCK_Pin;
    GPIO_Init(SCK_Port,&GPIO_InitStructure);    //ʱ������Ϊ ���� �������
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = MOSI_Pin;
    GPIO_Init(MOSI_Port,&GPIO_InitStructure);   //MOSI����Ϊ ���� �������
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = SS_Pin;
    GPIO_Init(SS_Port,&GPIO_InitStructure);     //Ƭѡ����Ϊ ͨ�� �������
    
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = MISO_Pin;
    GPIO_Init(MISO_Port,&GPIO_InitStructure);   //MISO����Ϊ ��������
    
    /*����SPI*/
    SPI_InitTypeDef SPI_InitSturcture;
    SPI_InitSturcture.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;//��Ƶϵ��
    SPI_InitSturcture.SPI_CPHA = SPI_CPHA_1Edge;    //��1�����ز��������룩
    SPI_InitSturcture.SPI_CPOL = SPI_CPOL_Low;      //CSKĬ�ϵ͵�ƽ    == ģʽ0
    SPI_InitSturcture.SPI_CRCPolynomial = 7;         //ָ��CRC����Ķ���ʽ��Ĭ��Ϊ7��
    SPI_InitSturcture.SPI_DataSize = SPI_DataSize_8b;//8λ����֡
    SPI_InitSturcture.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //������ȫ˫��
    SPI_InitSturcture.SPI_FirstBit = SPI_FirstBit_MSB;//��λ����
    SPI_InitSturcture.SPI_Mode = SPI_Mode_Master;   //����ģʽ
    SPI_InitSturcture.SPI_NSS = SPI_NSS_Soft;   //���NSS
    SPI_Init(SPI1, &SPI_InitSturcture);
    
    /*ʹ��SPI*/
    SPI_Cmd(SPI1,ENABLE);
    
    MySPI_W_SS(1);//��ʼ����ѡ�дӻ�
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
  * ��    ��������һ���ֽڣ�ģʽ0������������
  * ��    ����SendByte      �����͵��ֽ�
  * �� �� ֵ��ReceiveByte   ���յ����ֽ�
  * ע���������ʹ������λģ�͵ķ�ʽ��Ч�ʸ���
              ���Ҫ��Ϊģʽ1�������������ٷ��͡����½����ٽ��գ�2��3��ֱ�Ӹ�ʱ�Ӽ��Ծ�ok�ˣ�
  */
uint8_t MySPI_WarpByte(uint8_t SendByte)
{
    //�ȴ�TXE��־λΪ1 �����ͼĴ�����
    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) != SET);
    //���д�����ݵ����ͼĴ���
    SPI_I2S_SendData(SPI1,SendByte);
    //�ȴ�������ɣ���ʱ����Ҳһ����ɣ�
    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) != SET);
    //��ȡRDR
    return SPI_I2S_ReceiveData(SPI1);
} 




