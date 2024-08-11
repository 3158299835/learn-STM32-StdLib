#include "stm32f10x.h"                  // Device header





void AD_Init(void)
{
    //开启GPIOA时钟和ADC1外设时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    //配置ADC预分频器
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//12M
    //配置PA0
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    //手动在主函数中配置通道。达到切换的效果
    
    //初始化ADC
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;     //是否连续转换：否
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  //右对齐
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //外部触发：无
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;      //模式:独立ADC模式
    ADC_InitStructure.ADC_NbrOfChannel = 1;         //指定扫描模式下用几个通道
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;   //是否扫描模式：否
    ADC_Init(ADC1,&ADC_InitStructure);
    //开启ADC1
    ADC_Cmd(ADC1,ENABLE);
    
    //校准
    //复位校准、等待复位校准完成、开始校准、等待校准完成
    ADC_ResetCalibration(ADC1); //复位校准
    while(ADC_GetResetCalibrationStatus(ADC1) == SET) //等待复位校准完成
    ADC_StartCalibration(ADC1); //开始校准
    while(ADC_GetCalibrationStatus(ADC1) == SET); //等待校准完成
}


uint16_t AD_Getvalue(uint8_t ADC_Channel)
{
    //配置规则通道组
    ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);//规则组序列1的位置，配置为通道ADC_Channel
    //软件触发转换
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);//等待转换完成
    //获取转换值
    return ADC_GetConversionValue(ADC1);
}






















