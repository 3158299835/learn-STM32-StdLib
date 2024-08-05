#include "Serial.h"

//初始化
void Serial_Init(void)
{
    //使能A9 A10所在的GPIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    //使能A9 A10的复用外设时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    
    //配置PA9端口为复用推挽输出
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;       //9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化
    //这里对于F4芯片可以单独 分开的设置复用以及上下拉。不用分开配置，
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//复用推挽模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;       //9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);//初始化
    
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;//波特率。会自动算好填入BRR寄存器
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//硬件流控制、不使用.
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//用| 使用两个功能
    USART_InitStructure.USART_Parity = USART_Parity_No; //校验位。
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//停止位1位。
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //不需要校验，所以字长选择8位字长。
    USART_Init(USART1,&USART_InitStructure);
    
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NCIC_InitStructure;
    NCIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NCIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NCIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NCIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//优先级
    NVIC_Init(&NCIC_InitStructure);
    
    
    USART_Cmd(USART1,ENABLE);
    
    
}

//发送字节
void Serial_SendByte(uint16_t Byte)
{
    USART_SendData(USART1,Byte);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//如果写标志位没有置1（没有发送完），那么就等
}

//发送数组
void Serial_SendArray(uint8_t* Array,uint16_t len)
{
    uint16_t i = 0;
    for(i = 0; i < len; i++)
    {
        Serial_SendByte(Array[i]);
    }
}


//发送字符串
void Serial_SendString(char* String)//有结束的\0 所以不用再传长度了，
{
    uint16_t i = 0;
    for(i = 0; (String[i] != '\0'); i++)
    {
        Serial_SendByte(String[i]);
    }
}


//求次方函数
uint32_t Serial_Pow(uint32_t X,uint8_t Y)
{
    int Num = 1;
    while(Y--)
    {
        Num *= X;
    }
    return Num;
}


//发送字符形式的数字
void Serial_SendNumber(uint32_t Number,uint8_t len)
{
    //从高位像低位取数字然后输出
    uint8_t i = 0;
    for(i = 0; i < len; i++)
    {
        Serial_SendByte(Number / Serial_Pow(10,len - i - 1) %10 + '0');
    
    }
}

//下边没学过，直接搬过来的。
/**
  * 函    数：使用printf需要重定向的底层函数
  * 参    数：保持原始格式即可，无需变动
  * 返 回 值：保持原始格式即可，无需变动
  */
int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);			//将printf的底层重定向到自己的发送字节函数
	return ch;
}

/**
  * 函    数：自己封装的prinf函数
  * 参    数：format 格式化字符串
  * 参    数：... 可变的参数列表
  * 返 回 值：无
  */
void Serial_Printf(char *format, ...)
{
	char String[100];				//定义字符数组
	va_list arg;					//定义可变参数列表数据类型的变量arg
	va_start(arg, format);			//从format开始，接收参数列表到arg变量
	vsprintf(String, format, arg);	//使用vsprintf打印格式化字符串和参数列表到字符数组中
	va_end(arg);					//结束变量arg
	Serial_SendString(String);		//串口发送字符数组（字符串）
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


void USART1_IRQHandler(void)//中断
{
    if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET)
    {
        Serial_RxData = USART_ReceiveData(USART1);//读取
        Serial_RxFlag = 1;
        USART_ClearITPendingBit(USART1,USART_FLAG_RXNE);//手动清除标志位
    }

}

