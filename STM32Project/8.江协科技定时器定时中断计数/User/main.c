#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "Timer.h"

//��ʱ���жϼ�ʱ  ��++
uint16_t Num = 0;

int main()
{

    
    OLED_Init();//��ʼ��OLED;
    
    Timer_Init();//��ʼ��Timer
    

    OLED_ShowString(1,1,"Time:");
    while(1)
    {
        
        OLED_ShowNum(1,6,Num,5);
        
    }
}








