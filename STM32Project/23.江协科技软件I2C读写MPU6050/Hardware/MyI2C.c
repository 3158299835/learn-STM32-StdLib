#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define SCL_Clock   RCC_APB2Periph_GPIOA
#define SCL_PORT    GPIOA
#define SCL_Pin     GPIO_Pin_11

#define SDA_Clock   RCC_APB2Periph_GPIOA
#define SDA_PORT    GPIOA
#define SDA_Pin     GPIO_Pin_12


/**
  * 函    数：初始化I2C
  * 参    数：无
  * 返 回 值：无
  */
void MyI2C_Init(void)
{
    Delay_Init();//初始化延时函数
    
    /*开启SCL和SDA时钟*/
    RCC_APB2PeriphClockCmd(SCL_Clock,ENABLE);
    RCC_APB2PeriphClockCmd(SDA_Clock,ENABLE);
    
    /*初始化SCL和SDA引脚*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_InitStructure.GPIO_Pin = SCL_Pin;
    GPIO_Init(SCL_PORT,&GPIO_InitStructure);   //SCL配置为开漏输出
    
    GPIO_InitStructure.GPIO_Pin = SDA_Pin;
    GPIO_Init(SDA_PORT,&GPIO_InitStructure);   //SDA配置为开漏输出
    
    GPIO_SetBits(SCL_PORT,SCL_Pin);//拉高SCL
    GPIO_SetBits(SDA_PORT,SDA_Pin);//拉高SDA
}

/**
  * 函    数：写一位SCL
  * 参    数：0或1
  * 返 回 值：无
  */
void MyI2C_W_SCL (uint8_t BitValue)
{
    GPIO_WriteBit(SCL_PORT,SCL_Pin,(BitAction)BitValue);//BitAction是一个typedef的枚举类型值。
    Delay_us(10);   //延时，给从机读取时间
}

/**
  * 函    数：写一位SDA
  * 参    数：0或1
  * 返 回 值：无
  */
void MyI2C_W_SDA (uint8_t BitValue)
{
    GPIO_WriteBit(SDA_PORT,SDA_Pin,(BitAction)BitValue);
    Delay_us(10);   //延时，给从机读取时间
}

/**
  * 函    数：读一位SDA
  * 参    数：无
  * 返 回 值：BitValue
  */
uint8_t MyI2C_R_SDA (void)
{
    uint8_t BitValue = 0x00;   
    BitValue = GPIO_ReadInputDataBit(SDA_PORT,SDA_Pin);
    Delay_us(10);
    return BitValue;
}

/**
  * 函    数：起始时序单元
  * 参    数：无
  * 返 回 值：无
  */
void MyI2C_Start (void)
{
    MyI2C_W_SDA(1);
    MyI2C_W_SCL(1);//按照先SDA拉高再SCL拉高。防止在重复起始时触发终止条件
    MyI2C_W_SDA(0);
    MyI2C_W_SCL(0);//先SDA拉低，再SCL拉低。触发起始条件
}

/**
  * 函    数：结束时序单元
  * 参    数：无
  * 返 回 值：无
  */
void MyI2C_Stop (void)
{
    MyI2C_W_SDA(0);//在SCL为低电平时，先把SDA拉高，为后续做准备
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(1);//先SCL拉高，再SDA拉高。触发结束条件
}

/**
  * 函    数：发送一个字节
  * 参    数：Byte
  * 返 回 值：无
  */
void MyI2C_SendByte (uint8_t Byte)
{
    uint8_t i = 0;
    for(i = 0; i < 8; i++)
    {
        MyI2C_W_SDA( Byte & (0x80 >> i) );//按照最高位依次往右取出bit写入
        MyI2C_W_SCL(1);//从机读取
        MyI2C_W_SCL(0);//准备下次写入
    }
}

/**
  * 函    数：接收一个字节
  * 参    数：无
  * 返 回 值：Byte
  */
uint8_t MyI2C_ReceiveByte (void)
{
    MyI2C_W_SDA(1);//释放SDA控制
    uint8_t Byte = 0x00;//存放得到的bit
    
    uint8_t i = 0;
    for(i = 0; i < 8; i++)
    {
        MyI2C_W_SCL(1);//主机准备读取
        if (MyI2C_R_SDA() == 1)//如果读到的这一位为1
        {
            Byte |= (0x80 >> i);//就把这一位置1，否则默认为0
        }
        MyI2C_W_SCL(0);//从机放下一位bit的数据
    }
    return Byte;
}

/**
  * 函    数：发送应答
  * 参    数：AckBit
  * 返 回 值：无
  */
void MyI2C_SenndAck (uint8_t AckBit)
{
    
        MyI2C_W_SDA(AckBit);//应答
        MyI2C_W_SCL(1);//从机读取
        MyI2C_W_SCL(0);//准备下次动作
}

/**
  * 函    数：接收应答
  * 参    数：无
  * 返 回 值：reply
  */
uint8_t MyI2C_ReceiveAck (void)
{
    MyI2C_W_SDA(1);//释放SDA控制
    uint8_t AckBit = 0x00;//存放得到的bit

    MyI2C_W_SCL(1);//从机填写
    AckBit = MyI2C_R_SDA();//主机读取
    MyI2C_W_SCL(0);//准备下次动作
    return AckBit;
}












