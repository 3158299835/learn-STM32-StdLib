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
    AD_Init();
    
    while(1)
    {
            //显示通道
    OLED_ShowString(1,1,"AD1:");
    OLED_ShowString(2,1,"AD2:");
    OLED_ShowString(3,1,"AD3:");
    OLED_ShowString(4,1,"AD4:");
    
    
        
   //开启ADC 转换四条通道 1 次
    //然后DMA搬运到AD_Value数组中
    AD_Getvalue();


    //显示搬运后的数据
    OLED_ShowNum(1, 5, AD_Value[0], 4);
    OLED_ShowNum(2, 5, AD_Value[1], 4);
    OLED_ShowNum(3, 5, AD_Value[2], 4);
    OLED_ShowNum(4, 5, AD_Value[3], 4);
    Delay_ms(100);
        
 
    }
}




