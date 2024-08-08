#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
#include "Encoder.h"
#include "Timer.h"

/*
    ʹ��PA6 �� PA7 ���ŵĸ���ģʽ
    Ҳ����TIM3 ��CH1ͨ����CH2ͨ��
    ʹ�ñ������ӿ�
*/
int16_t Speed = 0;//��Timer.c���������ı��� 

int main(){
    OLED_Init();//��ʼ��OLED;
    Encoder_Init();//��ʼ��Encoder
//    Delay_Init();//��ʼ����ʱ����
    
    Timer_Init();//��ʼ����ʱ1s�жϺ���
    

    
    
    OLED_ShowString(1,1,"Num:");
    while(1)
    {
        OLED_ShowSignedNum(1,5,Speed,5);
//        Delay_ms(1000);
        
    }

}
    

