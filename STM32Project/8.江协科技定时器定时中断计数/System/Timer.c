#include "stm32f10x.h"                  // Device header

extern uint16_t Num;//��¼ʱ��ı�����������������main.c���Num�����ơ�

void Timer_Init(void)
{
    //����RCCʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//TIM2�ǹ�����APB1�����ϵ�
    //ѡ��ʱ����Ԫ��ԴΪ�ڲ�ʱ�ӡ���tim.hͷ�ļ�
    TIM_InternalClockConfig(TIM2);
    //����ʱ����Ԫ
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//��ʼ��ʱ����ԪҪ����Ľṹ��
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ָ��ʱ�ӷ�Ƶ��1��Ƶ
    //����ķ�Ƶ��Ϊ�˸��˲�������Ƶ��f  ��������N fԽ�͡�NԽ�ࡣ��������Խ�á�
    //���ź��ӳ�Խ��f�������ڲ�ʱ��ֱ�Ӷ�����Ҳ�����ɷ�Ƶ����Ƶ�ĵ���
    //����ķ�Ƶ�����Ƕ������˲�����f�ķ�Ƶ�����п��ơ�������ֱ����1�ͺã���ʱ����Ԫ��ϵ����
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//ѡ�����ģʽ���ֱ������ϡ����¡������������ģʽ
    TIM_TimeBaseStructure.TIM_Period = 10000 - 1;//ARR��װֵ  =  ֵ +1   �����������õ�ʱ��Ҫ-1.������ȷƥ�䡣������ARR��PSC��ʱ1s
    TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1;//PSC��Ƶ����Ƶϵ��= ֵ+1
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//�ظ�������������Ǹ߼����������еģ����ǲ���Ҫ�����Ը�0
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//��������ǳ�ʼ��ʱ����Ԫ�ġ�
    /*����������TIM_TimeBaseInit ����ʱ���������һ���ֶ�����һ�¸����¼�����Ϊ
    ��ʱ����ARR��װ�Ĵ��������Ƕ���һ�� Ӱ�ӼĴ���  ��ΪӰ�ӼĴ����Ĵ��ڡ�����д���ֵ����װ�Ĵ���ARR�ͼ�������ֵCNT������������Ч�����ǵȴ��˴����ڽ�����Ҳ�����ڸ����¼���ʱ��Ż���Ч�������������������ʱ���ֶ�������һ�¸����¼���
    ���������ǣ������¼��͸����ж���ͬʱ�������õġ����Դ�ʱ���жϱ�־λ�Ѿ���һ�ˡ����жϱ�־λ ���ֶ������һֱΪ1�������Ե���������֮�󣬻���������ж�һ�Ρ�
    �������ϵ縴λ֮���ڲ鿴������ʱ�Ѿ���1�ˣ�
    ����������������Ҫ�ֶ��������һ�´˴εĸ����жϱ�־λ*/
    TIM_ClearFlag(TIM2,TIM_IT_Update);          //������±�־λ
    //��������жϿ���
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//ʹ��TIM2�ĸ����жϵ�NVIC
    //����NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ѡ�����
    NVIC_InitTypeDef NVIC_InitStructuer;//����ṹ��
    NVIC_InitStructuer.NVIC_IRQChannel = TIM2_IRQn;//ѡ��ʱ��2��NVIC���ͨ��
    NVIC_InitStructuer.NVIC_IRQChannelCmd = ENABLE;//�Ƿ�ʹ��
    NVIC_InitStructuer.NVIC_IRQChannelPreemptionPriority = 2;//��ռ���ȼ�
    NVIC_InitStructuer.NVIC_IRQChannelSubPriority = 2;//��Ӧ���ȼ���
    NVIC_Init(&NVIC_InitStructuer);
    //���п��ƣ�ʹ�ܼ�����
    TIM_Cmd(TIM2,ENABLE);
}




//�����жϺ���
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)//����жϱ�־λ
    {
        Num++;
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}


