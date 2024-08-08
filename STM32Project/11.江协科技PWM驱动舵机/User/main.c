#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "pwm.h"
#include "key.h"



/*
    PA1�������PWM�����ƶ��
    ��������PWMռ�ձ�
    ��ʾ��OLED��Ļ��
    ���Ҫ������PWMҪ������20ms���ߵ�ƽ���Ҫ��0.5ms~2.5ms
    ��-  -90��    0.5ms
    �I   -45��    1ms
    ��   0��      1.5ms
    �J   45��     2ms
    ��   90��     2.5ms
*/
int main()
{
    
    OLED_Init();//��ʼ��OLED;
    Delay_Init();//��ʼ����ʱ
    PWM_Init();//��ʼ��PWM
    KEY_Init();//��ʼ��KEY
    
    
    
    OLED_ShowString(1,1,"CCR:");
    OLED_ShowString(2,1,"ARR:20000");
    
    OLED_ShowNum(1,5,0,4);
    uint16_t Num = 0;
    while(1)
    {
        if(!KEY_Get())//�͵�ƽ��Ч
        {
            Delay_ms(10);
            if(!KEY_Get())//ȷ��
            {
                while(!KEY_Get());//�ȴ��ɿ�
                Num += 500;
                if(Num > 2500)
                {
                    Num = 500;
                }
                OLED_ShowNum(1,5,Num,4);
                PWM_SetCompare2(Num);
            }
        
        }  
    }
}



