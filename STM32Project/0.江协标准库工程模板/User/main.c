#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "Key.h"

int main()
{

    
    LED_Init();//��ʼ��LED
    KEY_Init();//��ʼ��KEY

    while(1)
    {

    }
}
