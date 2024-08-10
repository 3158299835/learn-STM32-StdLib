#include "stm32f10x.h"                  // Device header



void IC_Init(void)
{
    //初始化TIM3和GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    
    //初始化GPIOA 6
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    //选择输入时钟
    TIM_InternalClockConfig(TIM3);
    
    //配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;//ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 -1;//PSC  基准1MHZ
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
    
    //清除更新标志
    TIM_ClearFlag(TIM3,TIM_IT_Update);
    
    //配置输入捕获单元
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM3,&TIM_ICInitStructure);
    
    //配置通道2
    TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);
    
    //配置从模式输入触发器
    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
    
    //配置从模式动作
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
    
    //使能定时器
    TIM_Cmd(TIM3,ENABLE);

}


uint16_t IC_GetFreq(void)
{
    //Freq = fc / N
    return  1000000 /  (TIM_GetCapture1(TIM3) + 1);
}

uint16_t IC_GetDuct(void)
{

    return (TIM_GetCapture2(TIM3) + 1 ) * 100 / (TIM_GetCapture1(TIM3)+1);
}




