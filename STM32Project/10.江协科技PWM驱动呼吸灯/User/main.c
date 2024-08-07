#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "pwm.h"
int main()
{
    OLED_Init();//初始化OLED;
    Delay_Init();//初始化延时
    PWM_Init();//初始化PWM

    
   OLED_ShowString(1,1,"PWM:");
    uint16_t i = 0;
    
    while(1)
    {
        for(i = 0; i <= 100; i++)
        {
            PWM_SetCompare1(i);
            Delay_ms(20);//延时，否则占空比变的太快10*100也就是1秒变亮
            OLED_ShowNum(1,5,i,3);
        }
        for(i = 0; i <= 100; i++)
        {
            PWM_SetCompare1(100 - i);//从100慢慢下降
            Delay_ms(20);
            OLED_ShowNum(1,5,(100 - i),3);
        }
        
        
    }
}



