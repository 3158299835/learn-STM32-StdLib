#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "oled.h"
#include "Delay.h"
#include "CountSensor.h"

int main()
{
    OLED_Init();//初始化OLED;
    CountSensor_Init();//初始化
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);//开启PWR外设
    
    OLED_ShowString(1,1,"Count:");
    while(1)
    {
        
        OLED_ShowSignedNum(1, 7,CountSenSor_Get(),5);
        
        
        OLED_ShowString(2,1,"Running");
        Delay_ms(100);
        OLED_ShowString(2,1,"       ");
        Delay_ms(100);
        
        PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);//开启电压调节器， WFI模式进入
        SystemInit();//重新启动主频
    }
}

