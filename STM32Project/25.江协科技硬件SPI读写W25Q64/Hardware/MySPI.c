#include "stm32f10x.h"                  // Device header

/*所用引脚列表*/
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
  * 函    数：MySPI初始化
  * 参    数：无
  * 返 回 值：无
  * 注意事项：无
  */
void MySPI_Init(void)
{   
    /*配置SPI、GPIO外设时钟*/
    RCC_APB2PeriphClockCmd(RCC_SPI1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_GPIO,ENABLE);
    /*配置引脚*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = SCK_Pin;
    GPIO_Init(SCK_Port,&GPIO_InitStructure);    //时钟配置为 复用 推挽输出
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = MOSI_Pin;
    GPIO_Init(MOSI_Port,&GPIO_InitStructure);   //MOSI配置为 复用 推挽输出
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = SS_Pin;
    GPIO_Init(SS_Port,&GPIO_InitStructure);     //片选配置为 通用 推挽输出
    
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = MISO_Pin;
    GPIO_Init(MISO_Port,&GPIO_InitStructure);   //MISO配置为 上拉输入
    
    /*配置SPI*/
    SPI_InitTypeDef SPI_InitSturcture;
    SPI_InitSturcture.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;//分频系数
    SPI_InitSturcture.SPI_CPHA = SPI_CPHA_1Edge;    //第1个边沿采样（读入）
    SPI_InitSturcture.SPI_CPOL = SPI_CPOL_Low;      //CSK默认低电平    == 模式0
    SPI_InitSturcture.SPI_CRCPolynomial = 7;         //指定CRC计算的多项式（默认为7）
    SPI_InitSturcture.SPI_DataSize = SPI_DataSize_8b;//8位数据帧
    SPI_InitSturcture.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //两根线全双工
    SPI_InitSturcture.SPI_FirstBit = SPI_FirstBit_MSB;//高位先行
    SPI_InitSturcture.SPI_Mode = SPI_Mode_Master;   //主机模式
    SPI_InitSturcture.SPI_NSS = SPI_NSS_Soft;   //软件NSS
    SPI_Init(SPI1, &SPI_InitSturcture);
    
    /*使能SPI*/
    SPI_Cmd(SPI1,ENABLE);
    
    MySPI_W_SS(1);//初始化不选中从机
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
  * 函    数：交换一个字节（模式0）（非连续）
  * 参    数：SendByte      待发送的字节
  * 返 回 值：ReceiveByte   接收到的字节
  * 注意事项：这是使用了移位模型的方式。效率更快
              如果要改为模式1，则先上升沿再发送。先下降沿再接收（2、3则直接改时钟极性就ok了）
  */
uint8_t MySPI_WarpByte(uint8_t SendByte)
{
    //等待TXE标志位为1 ，发送寄存器空
    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) != SET);
    //软件写入数据到发送寄存器
    SPI_I2S_SendData(SPI1,SendByte);
    //等待接收完成（这时发送也一定完成）
    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) != SET);
    //读取RDR
    return SPI_I2S_ReceiveData(SPI1);
} 




