#include "stm32f10x.h"                  // Device header



void IC_Init(void)
{
    //使能TIM2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    
    //使能GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    //配置PA0
    GPIO_InitTypeDef GOIO_InitStructure;
    GOIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GOIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GOIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOA,&GOIO_InitStructure);
    
    //配置时钟输入
    TIM_InternalClockConfig(TIM2);
    
    //配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;//ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;//PSC  标准时钟为频率为1M
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
    
    //清除配置时基单元后的中断标志位
    TIM_ClearFlag(TIM2,TIM_IT_Update);
    
    //配置IC输入捕获
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM2,&TIM_ICInitStructure);
    
    //配置通道二
    TIM_PWMIConfig(TIM2,&TIM_ICInitStructure);
    
    //配置主从模式
    //1.映射输入到TRGI通道
    TIM_SelectInputTrigger(TIM2,TIM_TS_TI1FP1);
    
    //2.选择从模式.清除计时器CNT
    TIM_SelectSlaveMode(TIM2,TIM_SlaveMode_Reset);
    
    //使能定时器
    TIM_Cmd(TIM2,ENABLE);
    

}



//得到被测函数频率
uint16_t IC_GetFreq(void)
{
    //fc为1M   N = TIM_GetCapture1 
    return 1000000 / (TIM_GetCapture1(TIM2) + 1);
}

//得到被测函数占空比
uint16_t IC_GetDuty(void)
{
    //CCR2  /  CCR1
    //下降沿CCR2会搬运CNT
    //上升沿CCR1会搬运CNT

    return (TIM_GetCapture2(TIM2) + 1)*100 / (TIM_GetCapture1(TIM2) + 1);
}




