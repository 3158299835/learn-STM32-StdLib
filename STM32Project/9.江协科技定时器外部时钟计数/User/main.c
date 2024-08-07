#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "Timer.h"

//��ʱ���ⲿ��ʱ num++
uint16_t Num = 0;

int main()
{

    
    OLED_Init();//��ʼ��OLED;
    
    Timer_Init();//��ʼ��Timer
    

    OLED_ShowString(1,1,"Num:");//10��+1
    OLED_ShowString(2,1,"CNT:");//0-9
    while(1)
    {
        
        OLED_ShowNum(1,6,Num,5);
        OLED_ShowNum(2,5,Timer_GetGounter(),5);
        
    }
}








