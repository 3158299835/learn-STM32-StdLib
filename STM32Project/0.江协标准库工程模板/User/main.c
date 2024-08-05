#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "Key.h"
#include "Serial.h"
int main()
{

    KEY_Init();//初始化KEY
    LED_Init();//初始化LED
    Delay_Init();//初始化延时函数
    
    Serial_Init();//初始化串口

    
//    Serial_SendByte(0x41);
//    Serial_SendByte('A');
    
//    uint8_t My_Array[] = {0x41,0x42,0x43,0x44};
    
//    char My_String[] = "Hello world";
    
//    Serial_SendArray(My_Array,4);
//    Serial_SendString(My_String);
    
//    Serial_SendString("Hello world\n");
//    Serial_SendNumber(12345,5);
    
//    Serial_Printf("num = %d",666);
    uint8_t RxData;
    while(1)
    {
        if(Serial_GetRxfalg() == 1)
        {
            RxData = Serial_GetRxData();
            Serial_SendByte(RxData);
        }
    }
}




