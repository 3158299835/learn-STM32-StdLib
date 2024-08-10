#include "stm32f10x.h"                  // Device header




void USART1_Init(void)
{
    //串口1通信， 引脚在PA 9 PA 10  9TX  10RX
    //使能GPIOA 。使能串口1外设
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

    //配置GPIO 9  10
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    //配置USART1
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600; 
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No; 
    USART_InitStructure.USART_StopBits = USART_StopBits_1; 
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    
    USART_Init(USART1,&USART_InitStructure);

    
    //使能接收移位寄存器的接收标志位
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    
    //配置NVIC
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);
    
    //使能USART1
    USART_Cmd(USART1,ENABLE);
}


//发送字符
void USART1_SendStr(char Data)
{
    USART_SendData(USART1,Data);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//等发完
}

//发送字符串
void USART1_SendString(char* Data)//输入一堆字符
{
    uint8_t i = 0;
    for(i = 0; (Data[i] != '\0'); i++)
    {
        USART1_SendStr(Data[i]);
    }
}




//接收数据包
extern char RXData[];
extern uint8_t RxFlag;

//获取接收到数据包标志位
uint8_t USART1_GetRxFlag(void)
{
    if(RxFlag == 1)
    {
        RxFlag = 0;//读取后归零
        return 1;
    }
    return 0;
}


//串口1的中断函数
void USART1_IRQHandler(void)
{
    static uint8_t RxState = 0;//状态机状态
    static uint8_t p = 0;//数组的‘指针’
    if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
    {
        uint8_t RxData = USART_ReceiveData(USART1);//存着此次接收到的值
        if (RxState == 0)//如果是包头
        {
            if (RxData == '@')         
            {
                RxState = 1;
                p = 0; //指针归零准备装载
            }
        }
        else if (RxState == 1)
        {
            if(RxData == '\r')//如果不是包尾
            {
                RxState = 2;
            }
            else
            {
                RXData[p] = RxData;//按照顺序存进去
                p++; //数组指针自增
            }
            
        }
        //当前状态为2，接收数据包包尾
        else if (RxState == 2)
        {
            if (RxData == '\n')//如果是最后的包尾
            {
                RxState = 0;
                RXData[p] = '\0';//添加字符串结束标志位 \0
                RxFlag = 1;//数据包接收标志位置1
            }
        }
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);//清除标志位
    }
}











