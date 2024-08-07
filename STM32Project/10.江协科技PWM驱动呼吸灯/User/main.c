#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "pwm.h"
int main()
{
    OLED_Init();//��ʼ��OLED;
    Delay_Init();//��ʼ����ʱ
    PWM_Init();//��ʼ��PWM

    
   OLED_ShowString(1,1,"PWM:");
    uint16_t i = 0;
    
    while(1)
    {
        for(i = 0; i <= 100; i++)
        {
            PWM_SetCompare1(i);
            Delay_ms(20);//��ʱ������ռ�ձȱ��̫��10*100Ҳ����1�����
            OLED_ShowNum(1,5,i,3);
        }
        for(i = 0; i <= 100; i++)
        {
            PWM_SetCompare1(100 - i);//��100�����½�
            Delay_ms(20);
            OLED_ShowNum(1,5,(100 - i),3);
        }
        
        
    }
}



