#include "stm32f10x.h"                  // Device header

/*所用引脚列表*/
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
  * 函    数：写片选信号SS
  * 参    数：BitValue：输入1片选信号SS为高电平
  * 返 回 值：无
  * 注意事项：无
  */
void MySPI_W_SS (uint8_t BitValue)
{
    GPIO_WriteBit(SS_Port,SS_Pin,(BitAction)BitValue);
}

/**
  * 函    数：写时钟信号SCK
  * 参    数：BitValue：输入1时钟信号SCK为高电平
  * 返 回 值：无
  * 注意事项：无
  */
void MySPI_W_SCK (uint8_t BitValue)
{
    GPIO_WriteBit(SCK_Port,SCK_Pin,(BitAction)BitValue);
}

/**
  * 函    数：写 主机输出，从机输入信号MOSI
  * 参    数：BitValue：输入1时主机输出高电平
  * 返 回 值：无
  * 注意事项：无
  */
void MySPI_W_MOSI (uint8_t BitValue)
{
    GPIO_WriteBit(MOSI_Port,MOSI_Pin,(BitAction)BitValue);
}

/**
  * 函    数：读 主机输入，从机输出信号MISO
  * 参    数：无
  * 返 回 值：BitValue
  * 注意事项：无
  */
uint8_t MySPI_R_MISO (void)
{
    return GPIO_ReadInputDataBit(MISO_Port,MISO_Pin);
}

/**
  * 函    数：MySPI初始化
  * 参    数：无
  * 返 回 值：无
  * 注意事项：无
  */
void MySPI_Init(void)
{   
    /*配置时钟与引脚*/
    RCC_APB2PeriphClockCmd(RCCPeriph,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = SCK_Pin | SS_Pin | MOSI_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MOSI_Port,&GPIO_InitStructure);   //时钟、片选、MOSI都是推挽输出
    
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = MISO_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(MISO_Port,&GPIO_InitStructure);   //MISO 为上拉输入
    
    MySPI_W_SS(1);  //片选默认为高
    MySPI_W_SCK(0); //时钟默认为低
}







/*******************/
/*SPI的三个时序单元*/
/*******************/





/**
  * 函    数：起始信号
  * 参    数：无
  * 返 回 值：无
  * 注意事项：无
  */
void MySPI_Start(void)
{   
    MySPI_W_SS(0);
}

/**
  * 函    数：终止条件
  * 参    数：无
  * 返 回 值：无
  * 注意事项：无
  */
void MySPI_Stop(void)
{   
    MySPI_W_SS(1);
}


/**
  * 函    数：交换一个字节（模式0）（方法1）
  * 参    数：SendByte      待发送的字节
  * 返 回 值：ReceiveByte   接收到的字节
  * 注意事项：这是使用掩码依次提取数据中的每一位保存或发送
              好处是不会改变传入参数本身，但是效率不高
              如果要改为模式1，则先上升沿再发送。先下降沿再接收（2、3则直接改时钟极性就ok了）
  */
//uint8_t MySPI_WarpByte(uint8_t SendByte)
//{
//    uint8_t ReceiveByte = 0x00;
//    
//    uint8_t i = 0;
//    for(i = 0; i < 8; i++)
//    {
//        MySPI_W_MOSI(SendByte & (0x80 >> i));  //发送第一个bit
//        MySPI_W_SCK(1);//第上升沿来临
//        if (MySPI_R_MISO() == 1)
//        {
//            ReceiveByte |= (0x80 >> i);    //按照从高往低接收数据
//        }
//        MySPI_W_SCK(0); //下降沿来临
//    }
//    return ReceiveByte;
//} 

/**
  * 函    数：交换一个字节（模式0）（方法2）
  * 参    数：SendByte      待发送的字节
  * 返 回 值：ReceiveByte   接收到的字节
  * 注意事项：这是使用了移位模型的方式。效率更快
              如果要改为模式1，则先上升沿再发送。先下降沿再接收（2、3则直接改时钟极性就ok了）
  */
uint8_t MySPI_WarpByte(uint8_t SendByte)
{
    uint8_t i = 0;
    for(i = 0; i < 8; i++)
    {
        MySPI_W_MOSI(SendByte & 0x80);  //发送第一个bit
        SendByte <<= 1; //发送数据左移一位
        MySPI_W_SCK(1); //第上升沿来临
        if (MySPI_R_MISO() == 1)
        {
            SendByte |= 0x01;    //保存收到的数据到发送寄存器的最低位
        }
        MySPI_W_SCK(0); //下降沿来临
    }
    return SendByte;
} 




