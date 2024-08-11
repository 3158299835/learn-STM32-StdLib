#include "stm32f10x.h"                  // Device header
#include "Freq.h"

extern uint16_t CCR;
extern uint16_t PSC;

void Timer_Init(void)
{
    //使用外部中断来控制PWM的占空比和频率
    
    //开启GPIO时钟  开启AFIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    //配置 PB0 11
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
   
    //配置AFIO 把 PA0 11映射到EXTI
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11);
    
    //配置EXTI
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line11;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger =EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);

    //配置NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);
    

}




//KEY1按下中断
void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line11) == SET)
    {
        CCR += 5;
        if(CCR > 100)
        {
            CCR = 0;
        }
        Freq_SetCCR(CCR);
        EXTI_ClearITPendingBit(EXTI_Line11);
    }
}

void EXTI0_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line0) == SET)
    {
        static uint8_t flag = 0;
        
        if(flag > 14)
        {
            flag = 0;
        }  
        switch (flag)
        {
            // 7200 - 1,  // 100 Hz
            case 1 : Freq_SetPSC(7200 - 1); break;
            // 3600 - 1,  // 200 Hz
            case 2 : Freq_SetPSC(3600 - 1); break;
            // 2400 - 1,  // 300 Hz
            case 3 : Freq_SetPSC(2400 - 1); break;
            // 1800 - 1,  // 400 Hz
            case 4 : Freq_SetPSC(1800 - 1); break;
            // 1440 - 1,  // 500 Hz
            case 5 : Freq_SetPSC(1440 - 1); break;
            // 1200 - 1,  // 600 Hz
            case 6 : Freq_SetPSC(1200 - 1); break;
            // 900 - 1,   // 800 Hz
            case 7 : Freq_SetPSC(900 - 1); break;
            // 800 - 1,   // 900 Hz
            case 8 : Freq_SetPSC(800 - 1); break;
            // 720 - 1,   // 1000 Hz
            case 9 : Freq_SetPSC(720 - 1); break;
            // 360 - 1,   // 2000 Hz
            case 10 : Freq_SetPSC(360 - 1); break;
            // 240 - 1,   // 3000 Hz
            case 11 : Freq_SetPSC(240 - 1); break;
            // 180 - 1,   // 4000 Hz
            case 12 : Freq_SetPSC(180 - 1); break;
            // 144 - 1,   // 5000 Hz
            case 13 : Freq_SetPSC(144 - 1); break;
            // 120 - 1,   // 6000 Hz
            case 14 : Freq_SetPSC(120 - 1); break;
        }
        flag++;
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}













