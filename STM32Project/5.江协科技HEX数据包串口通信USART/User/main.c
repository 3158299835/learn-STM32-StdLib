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
    
    Serial_Init();//��ʼ�������շ����ݰ�
    
    OLED_ShowString(1,1,"TX Packet:");//��OLED1��2����ʾ���͵����ݰ�
    OLED_ShowString(3,1,"RX Packet:");//��OLED1��4����ʾ���ܵ����ݰ�
    
    //��ʼ�������ڵ�����
    Serial_TxPacket[0] = 0x01;
    Serial_TxPacket[1] = 0x02;
    Serial_TxPacket[2] = 0x03;
    Serial_TxPacket[3] = 0x04;
    
    while(1)
    {
        if(KEY_Scan(0) == 2)//�������2���£���ô�Է��͵����ݰ������ֽ�++��Ȼ����ʾ����
        {
            
            Serial_TxPacket[0]++;
            Serial_TxPacket[1]++;
            Serial_TxPacket[2]++;
            Serial_TxPacket[3]++;
            //��ʾ
            OLED_ShowHexNum(2,1,Serial_TxPacket[0],2);
            OLED_ShowHexNum(2,4,Serial_TxPacket[1],2);
            OLED_ShowHexNum(2,7,Serial_TxPacket[2],2);
            OLED_ShowHexNum(2,10,Serial_TxPacket[3],2); 
            //�������ݰ�
            Serial_SendPacket();
        }

        
        
        //���յ������ݷŵ�OLED����ʾ
        if(Serial_GetRxFlag() == 1)
        {
            OLED_ShowHexNum(4,1,Serial_RxPacket[0],2);
            OLED_ShowHexNum(4,4,Serial_RxPacket[1],2);
            OLED_ShowHexNum(4,7,Serial_RxPacket[2],2);
            OLED_ShowHexNum(4,10,Serial_RxPacket[3],2);
        }
    

    }
}




