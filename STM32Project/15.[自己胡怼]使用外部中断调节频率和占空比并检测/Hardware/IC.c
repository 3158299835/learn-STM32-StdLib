#include "stm32f10x.h"                  // Device header



void IC_Init(void)
{
    //ʹ��TIM2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    
    //ʹ��GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    //����PA0
    GPIO_InitTypeDef GOIO_InitStructure;
    GOIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GOIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GOIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOA,&GOIO_InitStructure);
    
    //����ʱ������
    TIM_InternalClockConfig(TIM2);
    
    //����ʱ����Ԫ
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;//ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;//PSC  ��׼ʱ��ΪƵ��Ϊ1M
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
    
    //�������ʱ����Ԫ����жϱ�־λ
    TIM_ClearFlag(TIM2,TIM_IT_Update);
    
    //����IC���벶��
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM2,&TIM_ICInitStructure);
    
    //����ͨ����
    TIM_PWMIConfig(TIM2,&TIM_ICInitStructure);
    
    //��������ģʽ
    //1.ӳ�����뵽TRGIͨ��
    TIM_SelectInputTrigger(TIM2,TIM_TS_TI1FP1);
    
    //2.ѡ���ģʽ.�����ʱ��CNT
    TIM_SelectSlaveMode(TIM2,TIM_SlaveMode_Reset);
    
    //ʹ�ܶ�ʱ��
    TIM_Cmd(TIM2,ENABLE);
    

}



//�õ����⺯��Ƶ��
uint16_t IC_GetFreq(void)
{
    //fcΪ1M   N = TIM_GetCapture1 
    return 1000000 / (TIM_GetCapture1(TIM2) + 1);
}

//�õ����⺯��ռ�ձ�
uint16_t IC_GetDuty(void)
{
    //CCR2  /  CCR1
    //�½���CCR2�����CNT
    //������CCR1�����CNT

    return (TIM_GetCapture2(TIM2) + 1)*100 / (TIM_GetCapture1(TIM2) + 1);
}




