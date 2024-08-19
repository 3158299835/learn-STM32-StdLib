#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"

int main(void)
{
    /*ģ���ʼ��*/
    OLED_Init();        //OLED��ʼ��
    MyRTC_Init();       //RTC��ʼ��
    
    /*��ʾ��̬�ַ���*/
    OLED_ShowString(1, 1, "CNT:");  //ʱ���������
    OLED_ShowString(2, 1, "ALR:");  //����ֵ
    OLED_ShowString(3, 1, "ALRF:"); //���ӱ�־λ
    
    //����Ҫ��ʾ������ֵ�����ӼĴ���ֻ��д���ɶ�������Ҫ���£�������ʾ��
    uint32_t Alarm = RTC_GetCounter() + 10;
    //�趨����Ϊʮ���
    RTC_SetAlarm(Alarm);
    //��ʾ����
    OLED_ShowNum(2, 5, Alarm, 10);
    
    //����PWRʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    
    while (1)
    {
        OLED_ShowNum(1, 5, RTC_GetCounter(), 10);                   //��ʾ32λ���������
        OLED_ShowNum(3, 6, RTC_GetFlagStatus(RTC_FLAG_ALR), 1);     //��ʾ32λ���������
        
        OLED_ShowString(4,1,"Running");
        Delay_ms(100);
        OLED_ShowString(4,1,"       ");
        Delay_ms(100);
        
        //�ڽ������ģʽ֮ǰ��һ�㶼��Ҫ�����е����� ���رգ�������Ļ������ȵȡ�
        //�����������ʾһ��
        OLED_Clear();

        
        PWR_EnterSTANDBYMode();//�������ģʽ
    }
}
