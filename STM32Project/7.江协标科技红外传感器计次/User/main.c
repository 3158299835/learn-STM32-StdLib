#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "oled.h"

#include "CountSensor.h"
int main()
{
    OLED_Init();//��ʼ��OLED;
    CountSensor_Init();//��ʼ��

    
    OLED_ShowString(1,1,"Count:");
    while(1)
    {
        OLED_ShowSignedNum(1, 7,CountSenSor_Get(),5);
        
        
    }
}

