#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "pwm.h"
#include "key.h"



/*
    PA1引脚输出PWM波控制舵机
    按键调整PWM占空比
    显示在OLED屏幕上
    舵机要求输入PWM要求：周期20ms，高电平宽度要求0.5ms~2.5ms
    ←-  -90°    0.5ms
    ↖   -45°    1ms
    ↑   0°      1.5ms
    ↗   45°     2ms
    →   90°     2.5ms
*/
int main()
{
    
    OLED_Init();//初始化OLED;
    Delay_Init();//初始化延时
    PWM_Init();//初始化PWM
    KEY_Init();//初始化KEY
    
    
    
    OLED_ShowString(1,1,"CCR:");
    OLED_ShowString(2,1,"ARR:20000");
    
    OLED_ShowNum(1,5,0,4);
    uint16_t Num = 0;
    while(1)
    {
        if(!KEY_Get())//低电平有效
        {
            Delay_ms(10);
            if(!KEY_Get())//确定
            {
                while(!KEY_Get());//等待松开
                Num += 500;
                if(Num > 2500)
                {
                    Num = 500;
                }
                OLED_ShowNum(1,5,Num,4);
                PWM_SetCompare2(Num);
            }
        
        }  
    }
}



