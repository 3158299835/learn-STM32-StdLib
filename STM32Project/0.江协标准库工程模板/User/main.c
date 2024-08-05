#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "Key.h"

int main()
{

    
    LED_Init();//初始化LED
    KEY_Init();//初始化KEY

    while(1)
    {

    }
}
