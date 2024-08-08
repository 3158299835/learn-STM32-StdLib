#include "stm32f10x.h"                  // Device header



void PWM_Init(void)
{
    /*
        ����TIM2����ɵ�PWM
        ��PSC������Ƶ��
        ��CCR������ռ�ձ�
    */
    
    //ʹ��PA0�������
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    //ʹ��ʱ������
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    
    //ѡ��TIM2Ϊ�ڲ�ʱ�ӣ��������ô˺�����TIMĬ��ҲΪ�ڲ�ʱ��
    TIM_InternalClockConfig(TIM2);
    
    //����ʱ����Ԫ
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;\
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ָ���˲�������Ƶ��F�Ͳ�������NΪ ģʽ1
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;//ARR  ����Ϊ1 �����ﶨ��Ϊ100 - 1
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;//PSC 
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//�߼���ʱ���ĸ��ö�ʱ��
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
    
    //���ʱ����Ԫ���úú�����ı�־λ
    TIM_ClearFlag(TIM2,TIM_IT_Update);  
    
    //����OC����Ƚ�
    TIM_OCInitTypeDef TIM_OCInitStructure;//�����ṹ��
    TIM_OCStructInit(&TIM_OCInitStructure);//��ʼ���ṹ��,Ϊ�˱���û��ֵ����鷳
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//ѡ�����ģʽΪPWM1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//�Ƿ�ת��ƽ���ߵ�ƽ��Ч���ǵ͵�ƽ��Ч��
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƿ�ʹ�����
    TIM_OCInitStructure.TIM_Pulse = 0;//CCR�Ĵ���
    TIM_OC1Init(TIM2,&TIM_OCInitStructure);
    
    //ʹ�ܶ�ʱ��
    TIM_Cmd(TIM2,ENABLE);
    
    
}

//��װ����CCR�Ĵ����ĺ���
void PWM_SetCompare1(uint16_t Compare1)
{
    TIM_SetCompare1(TIM2,Compare1);
}


//��װ����PSC�Ĵ����ĺ���
void PWM_SetPrescaler(uint16_t Prescaler)
{
    TIM_PrescalerConfig(TIM2,Prescaler,TIM_PSCReloadMode_Immediate);
    //����ĵ����������� ѡ��������Ч�����ڸ��º���Ч��Ӱ�ӼĴ���Ԥװ�أ�
}





