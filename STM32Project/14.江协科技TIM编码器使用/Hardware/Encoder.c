#include "stm32f10x.h"                  // Device header

void Encoder_Init(void)
{
    //����GPIOA�Ͷ�ʱ�������ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    
    //����PA6��PA7
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    //���������й�ʱ�ӣ����ﲻ��Ҫ��������ʱ��
    
    //����ʱ����Ԫ 
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//�˲�����Ƶ����F N
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//����ģʽû�ã��ᱻ�������й�
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1; //һ��ѡ�������̼����������ڴ�0-1�ͻ���65535.����ǿ�ư�65536ת��Ϊ�з��������Ϳ��԰���ת��Ϊ������
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;//����Ƶ
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
    
    //�������벶��Ԫ���˲����ͱ�Ե����ѡ��
    //����Ľ�����ʼ������
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);//��ʼ���ṹ��
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//ͨ��Ϊ1
    TIM_ICInitStructure.TIM_ICFilter = 0XF;//�˲���Ϊ0xF
    TIM_ICInit(TIM3,&TIM_ICInitStructure);
    
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;//ͨ��Ϊ2
    TIM_ICInitStructure.TIM_ICFilter = 0XF;//�˲���Ϊ0xF
    TIM_ICInit(TIM3,&TIM_ICInitStructure);
    
    //�±���һ���ڱ������������У�����Ҫ���ã�
//    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//������ Ҳ���Ǹߵ͵�ƽ���Բ���ת  �ߵ�ƽ��Ч
//    TIM_ICInitStructure.TIM_ICPrescaler = ;  ������û������
//    TIM_ICInitStructure.TIM_ICSelection = ;  ������û������

    //ͨ��2���˲�������

    
    
    //���ñ������ӿ�  ѡ��TI12 ������       �Ƿ���
    TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
    
    TIM_Cmd(TIM3,ENABLE);
    
    
    
}




//��ȡ��������ֵ
//���������CNT
int16_t Encoder_Get(void)
{
    int16_t Temp = TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3,0);//����
    return Temp;
}






