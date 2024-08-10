#include "stm32f10x.h"                  // Device header




void USART1_Init(void)
{
    //����1ͨ�ţ� ������PA 9 PA 10  9TX  10RX
    //ʹ��GPIOA ��ʹ�ܴ���1����
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

    //����GPIO 9  10
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    //����USART1
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600; 
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No; 
    USART_InitStructure.USART_StopBits = USART_StopBits_1; 
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    
    USART_Init(USART1,&USART_InitStructure);

    
    //ʹ�ܽ�����λ�Ĵ����Ľ��ձ�־λ
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    
    //����NVIC
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);
    
    //ʹ��USART1
    USART_Cmd(USART1,ENABLE);
}


//�����ַ�
void USART1_SendStr(char Data)
{
    USART_SendData(USART1,Data);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//�ȷ���
}

//�����ַ���
void USART1_SendString(char* Data)//����һ���ַ�
{
    uint8_t i = 0;
    for(i = 0; (Data[i] != '\0'); i++)
    {
        USART1_SendStr(Data[i]);
    }
}




//�������ݰ�
extern char RXData[];
extern uint8_t RxFlag;

//��ȡ���յ����ݰ���־λ
uint8_t USART1_GetRxFlag(void)
{
    if(RxFlag == 1)
    {
        RxFlag = 0;//��ȡ�����
        return 1;
    }
    return 0;
}


//����1���жϺ���
void USART1_IRQHandler(void)
{
    static uint8_t RxState = 0;//״̬��״̬
    static uint8_t p = 0;//����ġ�ָ�롯
    if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
    {
        uint8_t RxData = USART_ReceiveData(USART1);//���Ŵ˴ν��յ���ֵ
        if (RxState == 0)//����ǰ�ͷ
        {
            if (RxData == '@')         
            {
                RxState = 1;
                p = 0; //ָ�����׼��װ��
            }
        }
        else if (RxState == 1)
        {
            if(RxData == '\r')//������ǰ�β
            {
                RxState = 2;
            }
            else
            {
                RXData[p] = RxData;//����˳����ȥ
                p++; //����ָ������
            }
            
        }
        //��ǰ״̬Ϊ2���������ݰ���β
        else if (RxState == 2)
        {
            if (RxData == '\n')//��������İ�β
            {
                RxState = 0;
                RXData[p] = '\0';//����ַ���������־λ \0
                RxFlag = 1;//���ݰ����ձ�־λ��1
            }
        }
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);//�����־λ
    }
}











