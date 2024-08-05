#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "Key.h"

int main()
{

    KEY_Init();//初始化KEY
    LED_Init();//初始化LED
    Delay_Init();//初始化延时函数
    


    while(1)
    {
        LED_ON(1);
        Delay_ms(500);
        LED_OFF(1);
        Delay_ms(500);
    }
}
