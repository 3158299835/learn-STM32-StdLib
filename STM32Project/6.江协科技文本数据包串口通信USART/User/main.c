#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "Key.h"
#include "Serial.h"
#include "oled.h"
#include "string.h"
int main()
{

    KEY_Init();//初始化KEY
    LED_Init();//初始化LED
    Delay_Init();//初始化延时函数
    OLED_Init();//初始化OLED;
    
    Serial_Init();//初始化串口收发数据包
    
    OLED_ShowString(1,1,"Result:");//在OLED1行2列显示当前命令执行结果
    OLED_ShowString(3,1,"RX Packet:");//在OLED1行4列显示接受的数据包
    
    //初始化数组内的内容
    
    while(1)
    {
        //接收到的数据放到OLED上显示
        if(Serial_GetRxFlag() == 1)//接收到数据
        {
            OLED_ShowString(4, 1, "                 ");
            OLED_ShowString(4, 1,Serial_RxPacket);
            
            
            if( strcmp(Serial_RxPacket,"LED_ON(1)" ) == 0)//如果=0则代表字符串相等
            {
                LED_ON(1);//执行命令并显示
                OLED_ShowString(2,1,"LED1_ON_OK");
            }
            else if( strcmp(Serial_RxPacket,"LED_ON(2)" ) == 0)//如果=0则代表字符串相等
            {
                LED_ON(2);//执行命令并显示
                OLED_ShowString(2,1,"LED2_ON_OK");
            }
            else if( strcmp(Serial_RxPacket,"LED_OFF(1)" ) == 0)//如果=0则代表字符串相等
            {
                LED_OFF(1);//执行命令并显示
                OLED_ShowString(2,1,"LED1_OFF_OK");
            }
            else if( strcmp(Serial_RxPacket,"LED_OFF(2)" ) == 0)//如果=0则代表字符串相等
            {
                LED_OFF(2);//执行命令并显示
                OLED_ShowString(2,1,"LED2_OFF_OK");
            }
            else
            {
                OLED_ShowString(2,1,"ERROR_CMD");
            }
            
            
            
            
        }
    

    }
}




