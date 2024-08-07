#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "Timer.h"

//定时器中断计时  秒++
uint16_t Num = 0;

int main()
{

    
    OLED_Init();//初始化OLED;
    
    Timer_Init();//初始化Timer
    

    OLED_ShowString(1,1,"Time:");
    while(1)
    {
        
        OLED_ShowNum(1,6,Num,5);
        
    }
}








