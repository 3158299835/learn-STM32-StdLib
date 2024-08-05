#include "led.h"


//��ʼ��LED
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


//Ϩ��LED
void LED_OFF(uint8_t num)
{
    if(num == 0)
    {
        return;
    }
    if(num == 1)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_12);
    }
    else if(num == 2)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_13);
    }
    else if(num == 3)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_14);
    }
    else if(num == 4)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_15);
    }
}

//����LED
void LED_ON(uint8_t num)
{
    if(num == 0)
    {
        return;
    }
    if(num == 1)
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_12);
    }
    else if(num == 2)
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_13);
    }
    else if(num == 3)
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_14);
    }
    else if(num == 4)
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_15);
    }
}

//��תLED
void LED_Flip(uint8_t num)
{
    if(num == 0)
    {
        return;
    }
    else if(num == 1)
    {
        if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12) == Bit_SET)
        {
            GPIO_ResetBits(GPIOB,GPIO_Pin_12);
        }
        else
        {
            GPIO_SetBits(GPIOB,GPIO_Pin_12);
        }
    }
    else if(num == 2)
    {
        if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_13) == Bit_SET)
        {
            GPIO_ResetBits(GPIOB,GPIO_Pin_13);
        }
        else
        {
            GPIO_SetBits(GPIOB,GPIO_Pin_13);
        }
    }
    else if(num == 3)
    {
        if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_14) == Bit_SET)
        {
            GPIO_ResetBits(GPIOB,GPIO_Pin_14);
        }
        else
        {
            GPIO_SetBits(GPIOB,GPIO_Pin_14);
        }
    }
    else if(num == 4)
    {
        if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_15) == Bit_SET)
        {
            GPIO_ResetBits(GPIOB,GPIO_Pin_15);
        }
        else
        {
            GPIO_SetBits(GPIOB,GPIO_Pin_15);
        }
    }
}
