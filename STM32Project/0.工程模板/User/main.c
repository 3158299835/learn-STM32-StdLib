#include "stm32f10x.h"                  // Device header

int main()
{
    //�Ĵ������
//    RCC->APB2ENR = 0x00000010;//��GPIOC��ʱ��
//    GPIOC->CRH = 0x00300000;//����PC13��Ϊ�������ģʽ���ٶ�Ϊ50MHz
//    GPIOC->ODR = 0x00000000;//����PC13��Ϊ�ߵ�ƽ
    //�⺯�����
    
    //��GPIOC��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    //����PC13�Ķ˿�Ϊ�������ģʽ���ٶ�Ϊ50MHz
    GPIO_InitTypeDef GPIO_InitStructure;                //����GPIO_Init�ĵڶ����������ṹ�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOC,&GPIO_InitStructure);//GPIO_Init������GPIOģʽ
    
    //����PC 13Ϊ�͵�ƽ����ơ�
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
    //GPIO_SetBits(GPIOC,GPIO_Pin_13);
    
    while(1)
    {
    
    
    
    }
}
