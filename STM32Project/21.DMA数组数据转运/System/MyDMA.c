#include "stm32f10x.h"                  // Device header

uint16_t MyDMA_size = 0;

void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t size)
{
    MyDMA_size = size;
    //开启DMA外设的时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    //初始化DMA参数
    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;//源基地址
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//源宽度
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;//源地址是否自增
    DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;//目标基地址
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//目标宽度 字节
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//目标是否自增
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//传输方向 1-存储器到外设。2-外设到 存储器
                    //因为我们后面要设置那个是外设那个是存储器，选哪个问题不大。
    DMA_InitStructure.DMA_BufferSize = size;//传输计数器  次数 0 - 65535
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//指定重装器是否要重装（注意不能应用在存储器到存储器的 软件重装模式
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable; //是否使用软件触发  是
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//选择优先级
    DMA_Init(DMA1_Channel1,&DMA_InitStructure);//软件触发，通道随便选。
    //使能DMA
    DMA_Cmd(DMA1_Channel1,DISABLE);//不让他立刻工作，而是调用函数后工作
}

//调用 后 转换一次
void MyDMA_Transfer(void)
{
    DMA_Cmd(DMA1_Channel1,DISABLE);//失能
    DMA_SetCurrDataCounter(DMA1_Channel1,MyDMA_size);
    DMA_Cmd(DMA1_Channel1,ENABLE);//使能
    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET)//等待转换完成标志位
    DMA_ClearFlag(DMA1_FLAG_TC1);//手动清除标志位，这个不会自动清除
    
    //GL全局标志位、  TC转运完成标志位、
    //HT转运过半标志位、  TE转运错误标志位
    
    //“GL” 是 “Global”（全局）的缩写。
    //“TC” 是 “Transfer Complete”（转运完成）的缩写。
    //“HT” 是 “Half Transfer”（转运过半）的缩写。
    //“TE” 是 “Transfer Error”（转运错误）的缩写。
}














