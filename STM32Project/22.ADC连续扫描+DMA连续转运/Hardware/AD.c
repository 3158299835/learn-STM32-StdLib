#include "stm32f10x.h"                  // Device header

uint16_t AD_Value[4];//定义用于存放AD转换结果的全局数组


void AD_Init(void)
{
    //开启GPIOA时钟、ADC1外设时钟、DMA外设的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    
    //配置ADC预分频器
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//12M
    
    //配置PA0
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    //配置规则通道
    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);//规则组序列1的位置，配置为通道0
    ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);//规则组序列2的位置，配置为通道1
    ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);//规则组序列3的位置，配置为通道2
    ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);//规则组序列4的位置，配置为通道3
    
    //初始化ADC
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;     //是否连续转换：是
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //右对齐
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //外部触发：无
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;      //模式:独立ADC模式
    ADC_InitStructure.ADC_NbrOfChannel = 4;         //用4个通道
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;   //是否扫描模式：是
    ADC_Init(ADC1,&ADC_InitStructure);
    
    
    /*ADC使能之前 开始配置DMA*/
    //初始化DMA参数
    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//源基地址
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//半字，16位
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//源地址是否自增：否
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;//目标基地址
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//目标宽度 字节
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//目的地否自增:是
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//传输方向 1-存储器到外设。2-外设到 存储器
    DMA_InitStructure.DMA_BufferSize = 4;//传输计数器   ：4次
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//指定重装器：循环
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //是否使用软件触发  否：
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//选择优先级
    DMA_Init(DMA1_Channel1,&DMA_InitStructure);//硬件触发，ADC1 的硬件触发在通道1 所以不能变
    //使能DMA
    DMA_Cmd(DMA1_Channel1, ENABLE);
    
    //开启ADC到DMA的输出
    ADC_DMACmd(ADC1, ENABLE);

    //开启ADC1
    ADC_Cmd(ADC1, ENABLE);
    
    //校准  
    ADC_ResetCalibration(ADC1); //复位校准
    while(ADC_GetResetCalibrationStatus(ADC1) == SET) //等待复位校准完成
    ADC_StartCalibration(ADC1); //开始校准
    while(ADC_GetCalibrationStatus(ADC1) == SET); //等待校准完成
    
    //软件触发ADC
     ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}























