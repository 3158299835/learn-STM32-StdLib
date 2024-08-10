#include "stm32f10x.h"                  // Device header


/*使用PA0输出可调PWM波*/
void PWM_Init(void)
{
    //初始化TIM2和GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    
    //初始化GPIOA 0
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    //选择输入时钟
    TIM_InternalClockConfig(TIM2);
    
    //配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;//ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 720 -1;//PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
    
    //清除更新标志
    TIM_ClearFlag(TIM2,TIM_IT_Update);
    
    //配置输出比较单元
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 50;
    TIM_OC1Init(TIM2,&TIM_OCInitStructure);
    
    //使能定时器
    TIM_Cmd(TIM2,ENABLE);
}


void PWM_SetFerq(uint16_t Ferq)
{
    //Ferq = 72000000 / 100 / (PSC + 1) = 720000 / (PSC + 1)
    //PSC = 720000 / Ferq - 1
    uint32_t PSC = 720000 / Ferq - 1;
    TIM_PrescalerConfig(TIM2,PSC,TIM_PSCReloadMode_Immediate);
}

void PWM_SetDuct(uint8_t Duct)
{
    TIM_SetCompare1(TIM2,Duct);

}



