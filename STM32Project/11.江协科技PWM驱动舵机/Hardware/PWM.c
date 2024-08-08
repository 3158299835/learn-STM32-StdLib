#include "stm32f10x.h"                  // Device header


/*
    ARR = 20000
    ռ�ձ�0.5ʱ
    RCC = 20000 * 0.5/20 = 500
*/

void PWM_Init(void)
{   
    //ʹ��PWM���������PA1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructuer;
    GPIO_InitStructuer.GPIO_Mode = GPIO_Mode_AF_PP;//ѡ���������������GPIO���ŵĿ���Ȩ����ƫ������
    GPIO_InitStructuer.GPIO_Pin = GPIO_Pin_1;//OCͨ�����
    GPIO_InitStructuer.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructuer);
    
    //ʹ��TIM2ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    
    //ѡ��ʱ��ԴΪ�ڲ�ʱ��
    TIM_InternalClockConfig(TIM2);
    
    //����ʱ����Ԫ
    TIM_TimeBaseInitTypeDef TIM_TImeBaseInitStructure;
    TIM_TImeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ָ��ʱ�ӷ�Ƶ
    TIM_TImeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //ѡ�����ģʽ
    TIM_TImeBaseInitStructure.TIM_Period = 20000 - 1; //�����Զ���װ�Ĵ���ARR
    TIM_TImeBaseInitStructure.TIM_Prescaler = 72 - 1; //���õ��������źŵķ�Ƶϵ��PSC
    TIM_TImeBaseInitStructure.TIM_RepetitionCounter = 0; //�ظ��������߼���ʱ�����õ�
    TIM_TimeBaseInit(TIM2,&TIM_TImeBaseInitStructure);
    
    /*
        ����Ƶ��Ϊ50HZ  ռ�ձ�0%  �ֱ���Ϊ0.05
        �ֱ���  =  1 / (��װ�Ĵ���ARR+1)               
        ռ�ձ�  = �ȽϿ���ֵCCR / (��װ�Ĵ���ARR+1��
        Ƶ��    =  ʱ��Ƶ��CK_PSC(72MHZ) / (Ԥ��ƵֵPSC+1)����װ�Ĵ���ARR+1��
        0.05 = 1 / ARR + 1  ----    ARR = 20000 - 1
        50 = 72M / ��psc+1����20000��      
        PSC+1 = 72   ---   PSC = 72 -1
    
    
    */
    
    //ʹ��OC�Ƚ�ͨ�� 1
    TIM_OCInitTypeDef TIM_OCInitStructure;  //���������߼���ʱ���ĳ�Ա��
    TIM_OCStructInit(&TIM_OCInitStructure); //����Ҫ�Ȱ�ÿ����Աһ����ʼֵ�����ⲻ��Ҫ������
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               //��������Ƚ�ģʽ - PWM1ģʽ
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //�Ƿ�ת -  ��
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //���ʹ�� - ʹ��
    TIM_OCInitStructure.TIM_Pulse = 0;       //����CCR�Ĵ�����ֵ��16λ
    
    TIM_OC2Init(TIM2,&TIM_OCInitStructure);//������OC2ͨ���������PA1������
    
    
    //ʹ�ܶ�ʱ��
    TIM_Cmd(TIM2,ENABLE);
    
    
}

void PWM_SetCompare2(uint16_t Compare2)//����Ϊͨ��2
{
    TIM_SetCompare2(TIM2,Compare2);
}



