#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "Key.h"
#include "Serial.h"
#include "OLED.h"

uint8_t RxData;

int main()
{
    OLED_Init();//初始化OLED
    
    Serial_Init();//初始化串口
    
    OLED_ShowString(1,1,"RxData:");
    while(1)
    {
        if(Serial_GetRxfalg() == 1)
        {
            RxData = Serial_GetRxData();
            Serial_SendByte(RxData);
            OLED_ShowHexNum(1,8,RxData,2);
        }
        OLED_ShowString(2,1,"Running");
        Delay_ms(100);
        OLED_ShowString(2,1,"       ");
        Delay_ms(100);
        
        __WFI();
    }
}




