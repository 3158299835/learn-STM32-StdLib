#include "Serial.h"

//��ʼ��
void Serial_Init(void)
{
    //ʹ��A9 A10���ڵ�GPIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    //ʹ��A9 A10�ĸ�������ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    
    //����PA9�˿�Ϊ�����������
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//��������ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;       //9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��
    //�������F4оƬ���Ե��� �ֿ������ø����Լ������������÷ֿ����ã�
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;       //9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);//��ʼ��
    
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;//�����ʡ����Զ��������BRR�Ĵ���
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ�������ơ���ʹ��.
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//��| ʹ����������
    USART_InitStructure.USART_Parity = USART_Parity_No; //У��λ��
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//ֹͣλ1λ��
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����ҪУ�飬�����ֳ�ѡ��8λ�ֳ���
    USART_Init(USART1,&USART_InitStructure);
    
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NCIC_InitStructure;
    NCIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NCIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NCIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NCIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//���ȼ�
    NVIC_Init(&NCIC_InitStructure);
    
    
    USART_Cmd(USART1,ENABLE);
    
    
}

//�����ֽ�
void Serial_SendByte(uint16_t Byte)
{
    USART_SendData(USART1,Byte);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//���д��־λû����1��û�з����꣩����ô�͵�
}

//��������
void Serial_SendArray(uint8_t* Array,uint16_t len)
{
    uint16_t i = 0;
    for(i = 0; i < len; i++)
    {
        Serial_SendByte(Array[i]);
    }
}


//�����ַ���
void Serial_SendString(char* String)//�н�����\0 ���Բ����ٴ������ˣ�
{
    uint16_t i = 0;
    for(i = 0; (String[i] != '\0'); i++)
    {
        Serial_SendByte(String[i]);
    }
}


//��η�����
uint32_t Serial_Pow(uint32_t X,uint8_t Y)
{
    int Num = 1;
    while(Y--)
    {
        Num *= X;
    }
    return Num;
}


//�����ַ���ʽ������
void Serial_SendNumber(uint32_t Number,uint8_t len)
{
    //�Ӹ�λ���λȡ����Ȼ�����
    uint8_t i = 0;
    for(i = 0; i < len; i++)
    {
        Serial_SendByte(Number / Serial_Pow(10,len - i - 1) %10 + '0');
    
    }
}

//�±�ûѧ����ֱ�Ӱ�����ġ�
/**
  * ��    ����ʹ��printf��Ҫ�ض���ĵײ㺯��
  * ��    ��������ԭʼ��ʽ���ɣ�����䶯
  * �� �� ֵ������ԭʼ��ʽ���ɣ�����䶯
  */
int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);			//��printf�ĵײ��ض����Լ��ķ����ֽں���
	return ch;
}

/**
  * ��    �����Լ���װ��prinf����
  * ��    ����format ��ʽ���ַ���
  * ��    ����... �ɱ�Ĳ����б�
  * �� �� ֵ����
  */
void Serial_Printf(char *format, ...)
{
	char String[100];				//�����ַ�����
	va_list arg;					//����ɱ�����б��������͵ı���arg
	va_start(arg, format);			//��format��ʼ�����ղ����б�arg����
	vsprintf(String, format, arg);	//ʹ��vsprintf��ӡ��ʽ���ַ����Ͳ����б��ַ�������
	va_end(arg);					//��������arg
	Serial_SendString(String);		//���ڷ����ַ����飨�ַ�����
}




uint8_t Serial_RxData;
uint8_t Serial_RxFlag;

uint8_t Serial_GetRxfalg(void)
{
    if(Serial_RxFlag == 1)
    {
        Serial_RxFlag = 0;
        return 1;
    }
    return 0;
}

uint8_t Serial_GetRxData(void)
{
    return Serial_RxData;
}


void USART1_IRQHandler(void)//�ж�
{
    if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET)
    {
        Serial_RxData = USART_ReceiveData(USART1);//��ȡ
        Serial_RxFlag = 1;
        USART_ClearITPendingBit(USART1,USART_FLAG_RXNE);//�ֶ������־λ
    }

}

