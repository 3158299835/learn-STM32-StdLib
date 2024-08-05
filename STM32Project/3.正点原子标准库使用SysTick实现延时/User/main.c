#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "Key.h"

int main()
{

    KEY_Init();//��ʼ��KEY
    LED_Init();//��ʼ��LED
    Delay_Init();//��ʼ����ʱ����
    


    while(1)
    {
        LED_ON(1);
        Delay_ms(500);
        LED_OFF(1);
        Delay_ms(500);
    }
}
