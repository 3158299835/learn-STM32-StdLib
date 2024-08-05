#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "Key.h"

int main()
{

    
    LED_Init();//��ʼ��LED
    KEY_Init();//��ʼ��KEY
    
    uint8_t KEY_Num = 0;

    while(1)
    {
        KEY_Num = KEY_Scan(0);
        LED_Flip(KEY_Num);
    }
}
