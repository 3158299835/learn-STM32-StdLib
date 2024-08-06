#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "Key.h"
#include "Serial.h"
#include "oled.h"
int main()
{

    KEY_Init();//��ʼ��KEY
    LED_Init();//��ʼ��LED
    Delay_Init();//��ʼ����ʱ����
    OLED_Init();//��ʼ��OLED;
    Serial_Init();//��ʼ������


    OLED_ShowString(1,4,"ing");//��whileѭ������ʾing
    
    uint16_t num = 0;
    while(1)
    {
       
         if(KEY1 == 1)//����1����
         {
            Delay_ms(10);//����
            if(KEY1 == 1)//ȷʵ�����ˡ�
            {
                 OLED_Clear();//���� ����ɿ���ť��  ��ʾing �ʹ����Ѿ�����λ
                while(KEY1 == 1)//�ȴ��ɿ�
                {
                    Delay_ms(10);
                    num++;
                    OLED_ShowNum(1,1,num,4);
                }
                if(num <= 0)
                {
                    ;
                }
                else if(num >= 300)//����������
                {
                    num = 0;
                    __set_FAULTMASK(1);     //ȫ���жϽ�ֹ
                    NVIC_SystemReset();     //��λ
                }
                else
                {
                    num = 0;
                    LED_Flip(1);
                }
            }
         
         }
    }
}




