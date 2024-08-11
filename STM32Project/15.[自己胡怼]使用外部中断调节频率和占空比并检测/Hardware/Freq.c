#include "stm32f10x.h"                  // Device header

void Freq_Init(void)
{
    //����ɵ���PWM
    //ʹ��ʱ�Ӻ�GPIO
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    //����PA6
    GPIO_InitTypeDef GPIO_InitSturucture;
    GPIO_InitSturucture.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitSturucture.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitSturucture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitSturucture);
    
    //��������ʱ��
    TIM_InternalClockConfig(TIM3);
    
    //����ʱ����Ԫ
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;//ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 720 -1;//PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);

    //���ʱ����Ԫ��ʼ��ʱ�����ĸ����¼�
    TIM_ClearFlag(TIM3,TIM_IT_Update);

    //��������Ƚϵ�ԪOC
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;//CCR
    TIM_OC1Init(TIM3,&TIM_OCInitStructure);
    
    TIM_Cmd(TIM3,ENABLE);

}


//�����޸�CCR��ֵ��ʵ��ռ�ձȵ���
void Freq_SetCCR(uint16_t Compare1)
{
    TIM_SetCompare1(TIM3,Compare1);

}

//��װ����Ƶ�ʵ��޸�PSC��
void Freq_SetPSC(uint16_t PSC)
{
    TIM_PrescalerConfig(TIM3,PSC,TIM_PSCReloadMode_Immediate);
}



