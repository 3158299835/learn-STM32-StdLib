#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"

#include "AD.h"
/*
    使用ADC1
    检测ADC通道1  PA0引脚的模拟电压
    在OLED显示
*/


uint8_t mode = 2;

uint16_t ADValue1 = 0;
uint16_t ADValue2 = 0;
uint16_t ADValue3 = 0;
uint16_t ADValue4 = 0;

float Voltage1 = 0;
float Voltage2 = 0;
float Voltage3 = 0;
float Voltage4 = 0; 

int main()
{
    OLED_Init();//初始化OLED;
    Delay_Init();
    AD_Init();//初始化AD

    if(mode == 1)
    {
        OLED_ShowString(1,1,"Value1:0000");
        OLED_ShowString(2,1,"Value2:0000");
        OLED_ShowString(3,1,"Value3:0000");
        OLED_ShowString(4,1,"Value4:0000");
    }
    else if(mode == 2)
    {
        OLED_ShowString(1,1,"Voltage1:0.00V");
        OLED_ShowString(2,1,"Voltage2:0.00V");
        OLED_ShowString(3,1,"Voltage3:0.00V");
        OLED_ShowString(4,1,"Voltage4:0.00V");
    }
    
    
    while(1)
    {
        
        
        if(mode == 1)
        {
            //显示数值
            ADValue1 = AD_Getvalue(ADC_Channel_0);
            ADValue2 = AD_Getvalue(ADC_Channel_1);
            ADValue3 = AD_Getvalue(ADC_Channel_2);
            ADValue4 = AD_Getvalue(ADC_Channel_3);
            OLED_ShowNum(1,8,ADValue1,4);
            OLED_ShowNum(2,8,ADValue2,4);
            OLED_ShowNum(3,8,ADValue3,4);
            OLED_ShowNum(4 ,8,ADValue4,4);
        }
        else if(mode == 2)
        {
            ADValue1 = AD_Getvalue(ADC_Channel_0);
            ADValue2 = AD_Getvalue(ADC_Channel_1);
            ADValue3 = AD_Getvalue(ADC_Channel_2);
            ADValue4 = AD_Getvalue(ADC_Channel_3);
            //显示转换的电压
            Voltage1 = (float)ADValue1 / 4095 * 3.3;
            Voltage2 = (float)ADValue2 / 4095 * 3.3;
            Voltage3 = (float)ADValue3 / 4095 * 3.3;
            Voltage4 = (float)ADValue4 / 4095 * 3.3;
            
            OLED_ShowNum(1,10,Voltage1,1);
            OLED_ShowNum(1,12,(uint16_t)(Voltage1 * 100 ) % 100, 2);
            OLED_ShowNum(2,10,Voltage2,1);
            OLED_ShowNum(2,12,(uint16_t)(Voltage2 * 100 ) % 100, 2);
            OLED_ShowNum(3,10,Voltage3,1);
            OLED_ShowNum(3,12,(uint16_t)(Voltage3 * 100 ) % 100, 2);
            OLED_ShowNum(4,10,Voltage4,1);
            OLED_ShowNum(4,12,(uint16_t)(Voltage4 * 100 ) % 100, 2);
        }
        Delay_ms(10);
    }
}



