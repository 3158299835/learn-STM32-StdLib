#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"//ֱ���õ���ʱ����
int main()
{

    
    LED_Init();//��ʼ��LED


    while(1)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_15);//PB15Ϊ�ߵ�ƽ��Ϩ��
        GPIO_ResetBits(GPIOB,GPIO_Pin_12);//PB12Ϊ�͵�ƽ������
        Delay_ms(500);//��ʱ500ms
        GPIO_SetBits(GPIOB,GPIO_Pin_12);//PB12Ϊ�ߵ�ƽ��Ϩ��
        GPIO_ResetBits(GPIOB,GPIO_Pin_13);//PB13Ϊ�͵�ƽ������
        Delay_ms(500);//��ʱ500ms
        GPIO_SetBits(GPIOB,GPIO_Pin_13);//PB13Ϊ�ߵ�ƽ��Ϩ��
        GPIO_ResetBits(GPIOB,GPIO_Pin_14);//PB14Ϊ�͵�ƽ������
        Delay_ms(500);//��ʱ500ms
        GPIO_SetBits(GPIOB,GPIO_Pin_14);//PB14Ϊ�ߵ�ƽ��Ϩ��
        GPIO_ResetBits(GPIOB,GPIO_Pin_15);//PB15Ϊ�͵�ƽ������
        Delay_ms(500);//��ʱ500ms
    }
}
