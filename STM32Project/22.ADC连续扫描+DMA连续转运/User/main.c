#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"

#include "AD.h"
/*



*/


int main()
{
    OLED_Init();//初始化OLED;
    Delay_Init();//初始化延时
    
    AD_Init();//开启AD连续转换，DMA连续搬运
    

    
    //显示通道
    OLED_ShowString(1,1,"AD1:");
    OLED_ShowString(2,1,"AD2:");
    OLED_ShowString(3,1,"AD3:");
    OLED_ShowString(4,1,"AD4:");
    OLED_ShowString(1,12,"0.00V");
    OLED_ShowString(2,12,"0.00V");
    OLED_ShowString(3,12,"0.00V");
    OLED_ShowString(4,12,"0.00V");
    
    //求电压
    float AD_Voltage1 = 0;
    float AD_Voltage2 = 0;
    float AD_Voltage3 = 0;
    float AD_Voltage4 = 0;
    
    while(1)
    {




    //显示搬运后的数据
    OLED_ShowNum(1, 5, AD_Value[0], 4);
    OLED_ShowNum(2, 5, AD_Value[1], 4);
    OLED_ShowNum(3, 5, AD_Value[2], 4);
    OLED_ShowNum(4, 5, AD_Value[3], 4);
    
    //显示转换的电压
    AD_Voltage1 = (float) AD_Value[0] / 4095 * 3.3;
    AD_Voltage2 = (float) AD_Value[1] / 4095 * 3.3;
    AD_Voltage3 = (float) AD_Value[2] / 4095 * 3.3;
    AD_Voltage4 = (float) AD_Value[3] / 4095 * 3.3;
    OLED_ShowNum(1,12,AD_Voltage1,1);
    OLED_ShowNum(1,14,(uint16_t)(AD_Voltage1 * 100 ) % 100, 2);
    OLED_ShowNum(2,12,AD_Voltage2,1);
    OLED_ShowNum(2,14,(uint16_t)(AD_Voltage2 * 100 ) % 100, 2);
    OLED_ShowNum(3,12,AD_Voltage3,1);
    OLED_ShowNum(3,14,(uint16_t)(AD_Voltage3 * 100 ) % 100, 2);
    OLED_ShowNum(4,12,AD_Voltage4,1);
    OLED_ShowNum(4,14,(uint16_t)(AD_Voltage4 * 100 ) % 100, 2);
    
    Delay_ms(20);
 
    }
}




