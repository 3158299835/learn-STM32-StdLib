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
    
    Serial_Init();//初始化串口收发数据包
    
    OLED_ShowString(1,1,"TX Packet:");//在OLED1行2列显示发送的数据包
    OLED_ShowString(3,1,"RX Packet:");//在OLED1行4列显示接受的数据包
    
    //初始化数组内的内容
    Serial_TxPacket[0] = 0x01;
    Serial_TxPacket[1] = 0x02;
    Serial_TxPacket[2] = 0x03;
    Serial_TxPacket[3] = 0x04;
    
    while(1)
    {
        if(KEY_Scan(0) == 2)//如果按键2按下，那么对发送的数据包所有字节++。然后显示发送
        {
            
            Serial_TxPacket[0]++;
            Serial_TxPacket[1]++;
            Serial_TxPacket[2]++;
            Serial_TxPacket[3]++;
            //显示
            OLED_ShowHexNum(2,1,Serial_TxPacket[0],2);
            OLED_ShowHexNum(2,4,Serial_TxPacket[1],2);
            OLED_ShowHexNum(2,7,Serial_TxPacket[2],2);
            OLED_ShowHexNum(2,10,Serial_TxPacket[3],2); 
            //发送数据包
            Serial_SendPacket();
        }

        
        
        //接收到的数据放到OLED上显示
        if(Serial_GetRxFlag() == 1)
        {
            OLED_ShowHexNum(4,1,Serial_RxPacket[0],2);
            OLED_ShowHexNum(4,4,Serial_RxPacket[1],2);
            OLED_ShowHexNum(4,7,Serial_RxPacket[2],2);
            OLED_ShowHexNum(4,10,Serial_RxPacket[3],2);
        }
    

    }
}




