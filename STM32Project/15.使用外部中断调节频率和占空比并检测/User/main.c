#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
#include "IC.h"
#include "Freq.h"
#include "Timer.h"

/*
    1.使用TIM2输出可调频率的方波
    2.使用TIM3的输入捕获测量频率
*/

uint16_t CCR = 50;
//范围 0 - 100

uint16_t PSC = 720 - 1;
//7200 - 1  100
//3600 - 1  200
//2400 - 1  300
//1800 - 1  400
//1440 - 1  500
//1200 - 1  600
//900 - 1   800
//800 - 1   900
//720 - 1   1000
//360 - 1   2000
//240 - 1   3000
//180 - 1   4000
//144 - 1   5000
//120 - 1   6000
//
int main()
{
    OLED_Init();//初始化OLED;
    IC_Init();//初始化IC
    Freq_Init();//初始化PWM波产生
    KEY_Init();//初始化按键
    Timer_Init();//初始化中断
    
    //初始化PWM
    Freq_SetCCR(CCR);
    Freq_SetPSC(PSC);
    
    OLED_ShowString(1,1,"Freq:00000HZ");
    OLED_ShowString(2,1,"Duty:00%");
    
    OLED_ShowString(3,1,"CCR:");
    OLED_ShowString(4,1,"PSC:");

    while(1)
    {
        //显示频率
        OLED_ShowNum(1,6,IC_GetFreq(),5);
        //显示占空比
        OLED_ShowNum(2,6,IC_GetDuty(),2);
        //显示CCR寄存器
        OLED_ShowNum(3,5,CCR,3);
        //显示PSC寄存器
        OLED_ShowNum(4,5,PSC,4);
    }
}



