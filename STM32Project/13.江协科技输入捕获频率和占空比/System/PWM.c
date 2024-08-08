#include "stm32f10x.h"                  // Device header



void PWM_Init(void)
{
    /*
        配置TIM2输出可调PWM
        让PSC来控制频率
        让CCR来控制占空比
    */
    
    //使能PA0输出引脚
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    //使能时钟外设
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    
    //选择TIM2为内部时钟，若不调用此函数，TIM默认也为内部时钟
    TIM_InternalClockConfig(TIM2);
    
    //配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;\
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//指定滤波器采样频率F和采样点数N为 模式1
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;//ARR  精度为1 。这里定义为100 - 1
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;//PSC 
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//高级定时器的复用定时器
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
    
    //清除时基单元配置好后产生的标志位
    TIM_ClearFlag(TIM2,TIM_IT_Update);  
    
    //配置OC输出比较
    TIM_OCInitTypeDef TIM_OCInitStructure;//创建结构体
    TIM_OCStructInit(&TIM_OCInitStructure);//初始化结构体,为了避免没赋值造成麻烦
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//选择输出模式为PWM1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//是否翻转电平（高电平有效还是低电平有效）
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//是否使能输出
    TIM_OCInitStructure.TIM_Pulse = 0;//CCR寄存器
    TIM_OC1Init(TIM2,&TIM_OCInitStructure);
    
    //使能定时器
    TIM_Cmd(TIM2,ENABLE);
    
    
}

//封装更改CCR寄存器的函数
void PWM_SetCompare1(uint16_t Compare1)
{
    TIM_SetCompare1(TIM2,Compare1);
}


//封装更改PSC寄存器的函数
void PWM_SetPrescaler(uint16_t Prescaler)
{
    TIM_PrescalerConfig(TIM2,Prescaler,TIM_PSCReloadMode_Immediate);
    //这里的第三个参数是 选择立刻生效还是在更新后生效（影子寄存器预装载）
}





