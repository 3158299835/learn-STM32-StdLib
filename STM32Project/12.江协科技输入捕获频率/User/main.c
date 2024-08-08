#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
#include "pwm.h"
#include "ic.h"
/*
    PA0���Ƶ�ʺ�ռ�ձȿɵ���PWM��
    PA6��Ϊ���� �����PA0��Ƶ�ʺ�ռ�ձ�
    ���ò��ܷ�
*/

int main()
{
    OLED_Init();//��ʼ��OLED;
    PWM_Init();//��ʼ��PWM
    IC_Init();//��ʼ��IC
    KEY_Init();//��ʼ��KEY
    
    //����Ƶ�ʺ�ռ�ձ�                         //(ARR+1)
    uint16_t Num = 720;
    PWM_SetPrescaler(Num - 1);  //1000HZ = 72M / 100 / (PSC+1)
    PWM_SetCompare1(50);        //ռ�ձ� = CCR/ARR  = CCR/100
    
    
    OLED_ShowString(1,1,"Freq:00000HZ");
    while(1)
    {
        //ѭ����ʾ��ǰ����
        OLED_ShowNum(1,6,IC_GetFreq(),5);
    }
}

