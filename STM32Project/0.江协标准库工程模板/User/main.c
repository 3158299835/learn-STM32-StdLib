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

    
    uint8_t RxData;
    while(1)
    {
        
        OLED_ShowString(1,1,"Hello World");
        if(Serial_GetRxfalg() == 1)
        {
            RxData = Serial_GetRxData();
            Serial_SendByte(RxData);
        }
    }
}




