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


uint16_t ADValue = 0;
float Voltage = 0;
    
int main()
{
    OLED_Init();//初始化OLED;
    Delay_Init();
    AD_Init();//初始化AD

    
    OLED_ShowString(1,1,"Value:0000");
    OLED_ShowString(2,1,"Voltage:0.00V");

    while(1)
    {
        ADValue = AD_Getvalue();
        Voltage = (float)ADValue / 4095 * 3.3;
        
        //显示数值
        OLED_ShowNum(1,7,ADValue,4);
        //显示转换的电压
        OLED_ShowNum(2,9,Voltage,1);
        OLED_ShowNum(2,11,(uint16_t)(Voltage * 100 ) % 100, 2);
        Delay_ms(10);
    }
}



