#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
#include "pwm.h"
#include "ic.h"
/*
    PA0输出频率和占空比可调的PWM波
    PA6作为输入 来检测PA0的频率和占空比
    采用测周法
*/

int main()
{
    OLED_Init();//初始化OLED;
    PWM_Init();//初始化PWM
    IC_Init();//初始化IC
    KEY_Init();//初始化KEY
    
    //设置频率和占空比                         //(ARR+1)
    PWM_SetPrescaler(720 - 1);  //1000HZ = 72M / 100 / (PSC+1)
    PWM_SetCompare1(50);        //占空比 = CCR/ARR  = CCR/100
    
    
    OLED_ShowString(1,1,"Freq:00000HZ");
    OLED_ShowString(2,1,"Buty:00%");
    while(1)
    {
        //循环显示当前周期
        OLED_ShowNum(1,6,IC_GetFreq(),5);
        OLED_ShowNum(2,6,IC_GetButy(),2);;
    }
}

