#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "Key.h"
#include "Serial.h"
#include "oled.h"
int main()
{

    KEY_Init();//初始化KEY
    LED_Init();//初始化LED
    Delay_Init();//初始化延时函数
    OLED_Init();//初始化OLED;
    Serial_Init();//初始化串口

    
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




