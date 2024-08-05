#include "led.h"
#include "stm32f10x.h"

void LED_Init(void)
{
    //���������ΪPB 12 13 14 15,LEDΪ�͵�ƽ��Ч
    
        
    //F4��оƬ�����ﻹ��Ҫ��������������PuPd �Լ� ������߿�©Otype
    
    //��GPIOB��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    //����GPIO_Init�ĵڶ����������ṹ�����
    GPIO_InitTypeDef GPIO_InitStructure;                
    //����C99�²���Ҫ�ŵ��ڵ�һ��
    
    
    //�����GPIO�Ƿֿ����õģ���ʵ����д��A||B.�����Ͳ���д��ô����ˡ������ҾͲ�����
    
    
    //PB12
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //����PC13�Ķ˿�Ϊ�������ģʽ���ٶ�Ϊ50MHz
    
    GPIO_Init(GPIOB,&GPIO_InitStructure);//GPIO_Init����ʼ��GPIO B��PB12��GPIO
    GPIO_SetBits(GPIOB,GPIO_Pin_12);//����GPIOΪ�ߵ�ƽ��LEDΪϨ��
    //
    
   //PB13
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_13);
    
   //PB14
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_14);
    
    
   //PB15
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_15);

}

