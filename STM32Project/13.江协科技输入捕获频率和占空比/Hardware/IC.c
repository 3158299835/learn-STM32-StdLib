#include "stm32f10x.h"                  // Device header




//��ʼ��
void IC_Init(void)
{
   /*
        ����TIm3��ͨ��1���ţ�PA6����ȡ�ź�
    */
    
    //ʹ��PA0�������
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//PA6
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    //ʹ��ʱ������
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    
    //ѡ��TIM2Ϊ�ڲ�ʱ�ӣ��������ô˺�����TIMĬ��ҲΪ�ڲ�ʱ��
    TIM_InternalClockConfig(TIM3);
    
    //����ʱ����Ԫ
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;\
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ָ���˲�������Ƶ��F�Ͳ�������NΪ ģʽ1
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;//������CNT���������ֵ����Ƶ�����Ҫ���ô�һЩ����ֹ�������
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;//�����˲��ܷ��ı�׼Ƶ��fc����ʱ�ȶ���Ϊ1MHZ
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//�߼���ʱ���ĸ��ö�ʱ��
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
    
    //���ʱ����Ԫ���úú�����ı�־λ
    TIM_ClearFlag(TIM3,TIM_IT_Update);
    
    //����ͨ��һ
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//ѡ��ͨ��1
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//��������Ч
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//�����źŷ�Ƶ��
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//ֱ������
    TIM_ICInit(TIM3,&TIM_ICInitStructure);
    
    //��������PWMI�������ͷ���һ��ͬ�� ������ж�Ȼ�����Ū���෴�ģ����Կ�F2��
    //��ֻ֧��ͨ��1 ��ͨ��2 �����ã����ܴ���ͨ��3 4��
    TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);
//    //����ͨ����������һ������һ�ݣ�
//    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;//ѡ��ͨ��2
//    TIM_ICInitStructure.TIM_ICFilter = 0xF;
//    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;//�½�����Ч
//    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//�����źŷ�Ƶ��
//    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;//��������
//    TIM_ICInit(TIM3,&TIM_ICInitStructure);
    
    //��������ģʽ��TRGI�Ĵ���ԴΪTI1FP1
    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
    
    //���ô�ģʽΪreset
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);//��ȡ���Զ����
    
    //ʹ�ܶ�ʱ��
    TIM_Cmd(TIM3,ENABLE);
}


//��ȡƵ��
uint32_t IC_GetFreq(void)
{
    //ִ�й�ʽ��fx = fc / N  fc = 1M
    return 1000000 / (TIM_GetCapture1(TIM3)+1);//��ȡTIM3��ͨ��1��CCR��ֵ
    // +1 Ϊ���������...��Ϊ1000HZ��ʾ����1001
    //+1 ��ԭ������Ϊÿ�ζ����ټ�¼һ����+1����999+1 ��������������
}



//��ȡռ�ձ�
uint32_t IC_GetButy(void)
{
    //�½��صļ��� ���� �����ؼ�������ռ�ձ�
    //�½��ؼǵ�������ͨ������CCR2�У������ؼǵ�������CCR1�С�
    return (TIM_GetCapture2(TIM3) + 1 ) * 100 / (TIM_GetCapture1(TIM3) + 1);//*100����ʵ���� 1%~100%
    //CCR�ܻ���һ�������������������

}


