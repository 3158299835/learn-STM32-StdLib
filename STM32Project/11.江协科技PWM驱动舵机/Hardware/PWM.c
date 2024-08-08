#include "stm32f10x.h"                  // Device header


/*
    ARR = 20000
    占空比0.5时
    RCC = 20000 * 0.5/20 = 500
*/

void PWM_Init(void)
{   
    //使能PWM的输出引脚PA1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructuer;
    GPIO_InitStructuer.GPIO_Mode = GPIO_Mode_AF_PP;//选择复用推挽输出，把GPIO引脚的控制权交给偏上外设
    GPIO_InitStructuer.GPIO_Pin = GPIO_Pin_1;//OC通道输出
    GPIO_InitStructuer.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructuer);
    
    //使能TIM2时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    
    //选择时钟源为内部时钟
    TIM_InternalClockConfig(TIM2);
    
    //配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TImeBaseInitStructure;
    TIM_TImeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //指定时钟分频
    TIM_TImeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //选择计数模式
    TIM_TImeBaseInitStructure.TIM_Period = 20000 - 1; //配置自动重装寄存器ARR
    TIM_TImeBaseInitStructure.TIM_Prescaler = 72 - 1; //配置到计数器信号的分频系数PSC
    TIM_TImeBaseInitStructure.TIM_RepetitionCounter = 0; //重复计数，高级定时器才用到
    TIM_TimeBaseInit(TIM2,&TIM_TImeBaseInitStructure);
    
    /*
        产生频率为50HZ  占空比0%  分辨率为0.05
        分辨率  =  1 / (重装寄存器ARR+1)               
        占空比  = 比较控制值CCR / (重装寄存器ARR+1）
        频率    =  时钟频率CK_PSC(72MHZ) / (预分频值PSC+1)（重装寄存器ARR+1）
        0.05 = 1 / ARR + 1  ----    ARR = 20000 - 1
        50 = 72M / （psc+1）（20000）      
        PSC+1 = 72   ---   PSC = 72 -1
    
    
    */
    
    //使能OC比较通道 1
    TIM_OCInitTypeDef TIM_OCInitStructure;  //不用引出高级定时器的成员。
    TIM_OCStructInit(&TIM_OCInitStructure); //但是要先把每个成员一个初始值，避免不必要的问题
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               //设置输出比较模式 - PWM1模式
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //是否反转 -  否
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //输出使能 - 使能
    TIM_OCInitStructure.TIM_Pulse = 0;       //配置CCR寄存器的值。16位
    
    TIM_OC2Init(TIM2,&TIM_OCInitStructure);//配置在OC2通道。输出在PA1引脚上
    
    
    //使能定时器
    TIM_Cmd(TIM2,ENABLE);
    
    
}

void PWM_SetCompare2(uint16_t Compare2)//更改为通道2
{
    TIM_SetCompare2(TIM2,Compare2);
}



