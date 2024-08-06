#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "Key.h"
#include "Serial.h"
#include "oled.h"
#include "string.h"
int main()
{

    KEY_Init();//��ʼ��KEY
    LED_Init();//��ʼ��LED
    Delay_Init();//��ʼ����ʱ����
    OLED_Init();//��ʼ��OLED;
    
    Serial_Init();//��ʼ�������շ����ݰ�
    
    OLED_ShowString(1,1,"Result:");//��OLED1��2����ʾ��ǰ����ִ�н��
    OLED_ShowString(3,1,"RX Packet:");//��OLED1��4����ʾ���ܵ����ݰ�
    
    //��ʼ�������ڵ�����
    
    while(1)
    {
        //���յ������ݷŵ�OLED����ʾ
        if(Serial_GetRxFlag() == 1)//���յ�����
        {
            OLED_ShowString(4, 1, "                 ");
            OLED_ShowString(4, 1,Serial_RxPacket);
            
            
            if( strcmp(Serial_RxPacket,"LED_ON(1)" ) == 0)//���=0������ַ������
            {
                LED_ON(1);//ִ�������ʾ
                OLED_ShowString(2,1,"LED1_ON_OK");
            }
            else if( strcmp(Serial_RxPacket,"LED_ON(2)" ) == 0)//���=0������ַ������
            {
                LED_ON(2);//ִ�������ʾ
                OLED_ShowString(2,1,"LED2_ON_OK");
            }
            else if( strcmp(Serial_RxPacket,"LED_OFF(1)" ) == 0)//���=0������ַ������
            {
                LED_OFF(1);//ִ�������ʾ
                OLED_ShowString(2,1,"LED1_OFF_OK");
            }
            else if( strcmp(Serial_RxPacket,"LED_OFF(2)" ) == 0)//���=0������ַ������
            {
                LED_OFF(2);//ִ�������ʾ
                OLED_ShowString(2,1,"LED2_OFF_OK");
            }
            else
            {
                OLED_ShowString(2,1,"ERROR_CMD");
            }
            
            
            
            
        }
    

    }
}




