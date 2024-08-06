#include "stm32f10x.h"                  // Device header

//����ΪA2  

//�ƴα���
uint16_t CountSensor_Count = 0;

//��ʼ��
void CountSensor_Init(void)
{
    //����A2��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //����������APB2�����AFIO����ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    //EXTIʱ�Ӻ�NVIC��ʱ�Ӳ����ֶ��򿪡�
    
    //����GPIO
    GPIO_InitTypeDef GPIO_InitStructrue;
    GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_IPU;        //��������ģʽ
    GPIO_InitStructrue.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_50MHz;    
    GPIO_Init(GPIOA,&GPIO_InitStructrue);
    
    //����AFIO ��F1����GPIO.h�ļ��У���Ŀ����Ϊ�˰�GPIOA��PIN2����ӳ�䵽AFIO�С���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);//������Ҫ����PIn��GPIOx��ѡ��

    
    //����EXTI
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;          //ѡ���ж���·��������PIN2 ����Ϊ2   
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;           //�Ƿ�ʹ��ָ�����ж���·
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //�жϻ���Ӧģʽ   
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�������½�����ش���
    EXTI_Init(&EXTI_InitStructure);
    
    //����NVIC����ΪNVIC�����ںˣ����Ա����䵽�ں˵�������ȥ�ˣ���misc.c��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//������ռ����Ӧ���ȼ�
     
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;       //��stm32f10x.h�ļ��������IRQn_Type���һ���ж�ͨ��������ʹ�õ���md��оƬ�����������15-10����9-5����Ҫȥ�Ҷ�Ӧ���Ǹ�����������PIN2.������2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //�Ƿ�ʹ��ָ�����ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ���������Կ�������Χ����
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;       //ָ����Ӧ���ȼ�
    NVIC_Init(&NVIC_InitStructure);    
    
   
    
}



//��ȡ��ǰ�ļ���
uint16_t CountSenSor_Get(void)
{
    return CountSensor_Count;
}


//��STM32�У��жϵĺ������ǹ̶��ġ������������ļ��д��xxx.s 
//��IRQHandler��β�ľ����жϺ��������֡�
//��������Ҫ�ҵ���Ӧ���жϺ�������������2
void EXTI2_IRQHandler(void)//�жϺ������޲��޷���ֵ�ġ��жϺ�������д�ԣ�д��ͽ���ȥ
{
    //�ڽ����жϺ�һ��Ҫ�ж�һ������ǲ���������Ҫ���Ǹ��ж�Դ�������жϡ�
    //�������������GPIOA��PIN2���ţ����Բ���д��
    //�����5-9 10-15�����š�����EXTI��NVIC�Ǽ������õġ�
    //������Ҫ����EXTI����ʱ��16�����š����ж���16�����ŵ���һ�����͵��ж�����
    //����淶д�Ļ���Ҫ����ȥ
    //���ұ�־λ������exit.h�С�
    if(EXTI_GetITStatus(EXTI_Line2) == SET)//��һ������������.�ж�����ߵı�־λ�ǲ���== SET��������������Ҫ��
    {
    
        CountSensor_Count++;
        EXTI_ClearITPendingBit(EXTI_Line2);//�жϽ�����Ҫ���������־λ�ĺ���������㲻����������һֱ�����ж�
    }
}















