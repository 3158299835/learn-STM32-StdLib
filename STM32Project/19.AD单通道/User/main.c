#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"

#include "AD.h"
/*
    ʹ��ADC1
    ���ADCͨ��1  PA0���ŵ�ģ���ѹ
    ��OLED��ʾ
*/


uint16_t ADValue = 0;
float Voltage = 0;
    
int main()
{
    OLED_Init();//��ʼ��OLED;
    Delay_Init();
    AD_Init();//��ʼ��AD

    
    OLED_ShowString(1,1,"Value:0000");
    OLED_ShowString(2,1,"Voltage:0.00V");

    while(1)
    {
        ADValue = AD_Getvalue();
        Voltage = (float)ADValue / 4095 * 3.3;
        
        //��ʾ��ֵ
        OLED_ShowNum(1,7,ADValue,4);
        //��ʾת���ĵ�ѹ
        OLED_ShowNum(2,9,Voltage,1);
        OLED_ShowNum(2,11,(uint16_t)(Voltage * 100 ) % 100, 2);
        Delay_ms(10);
    }
}



