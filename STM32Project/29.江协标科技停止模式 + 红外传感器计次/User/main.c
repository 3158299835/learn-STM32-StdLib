#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "oled.h"
#include "Delay.h"
#include "CountSensor.h"

int main()
{
    OLED_Init();//��ʼ��OLED;
    CountSensor_Init();//��ʼ��
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);//����PWR����
    
    OLED_ShowString(1,1,"Count:");
    while(1)
    {
        
        OLED_ShowSignedNum(1, 7,CountSenSor_Get(),5);
        
        
        OLED_ShowString(2,1,"Running");
        Delay_ms(100);
        OLED_ShowString(2,1,"       ");
        Delay_ms(100);
        
        PWR_EnterSTOPMode(PWR_Regulator_ON,PWR_STOPEntry_WFI);//������ѹ�������� WFIģʽ����
        SystemInit();//����������Ƶ
    }
}

