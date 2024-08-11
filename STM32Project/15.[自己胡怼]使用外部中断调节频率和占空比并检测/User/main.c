#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
#include "IC.h"
#include "Freq.h"
#include "Timer.h"

/*
    1.ʹ��TIM2����ɵ�Ƶ�ʵķ���
    2.ʹ��TIM3�����벶�����Ƶ��
*/

uint16_t CCR = 50;
//��Χ 0 - 100

uint16_t PSC = 720 - 1;
//7200 - 1  100
//3600 - 1  200
//2400 - 1  300
//1800 - 1  400
//1440 - 1  500
//1200 - 1  600
//900 - 1   800
//800 - 1   900
//720 - 1   1000
//360 - 1   2000
//240 - 1   3000
//180 - 1   4000
//144 - 1   5000
//120 - 1   6000
//
int main()
{
    OLED_Init();//��ʼ��OLED;
    IC_Init();//��ʼ��IC
    Freq_Init();//��ʼ��PWM������
    KEY_Init();//��ʼ������
    Timer_Init();//��ʼ���ж�
    
    //��ʼ��PWM
    Freq_SetCCR(CCR);
    Freq_SetPSC(PSC);
    
    OLED_ShowString(1,1,"Freq:00000HZ");
    OLED_ShowString(2,1,"Duty:00%");
    
    OLED_ShowString(3,1,"CCR:");
    OLED_ShowString(4,1,"PSC:");

    while(1)
    {
        //��ʾƵ��
        OLED_ShowNum(1,6,IC_GetFreq(),5);
        //��ʾռ�ձ�
        OLED_ShowNum(2,6,IC_GetDuty(),2);
        //��ʾCCR�Ĵ���
        OLED_ShowNum(3,5,CCR,3);
        //��ʾPSC�Ĵ���
        OLED_ShowNum(4,5,PSC,4);
    }
}



