#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "oled.h"

#include "CountSensor.h"
int main()
{
    OLED_Init();//初始化OLED;
    CountSensor_Init();//初始化

    
    OLED_ShowString(1,1,"Count:");
    while(1)
    {
        OLED_ShowSignedNum(1, 7,CountSenSor_Get(),5);
        
        
    }
}

