#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
/*
    �������Ź����Գ���
    ι��ʱ��Ϊ1s��

*/

int main()
{
    OLED_Init();//��ʼ��OLED;
    Delay_Init();
    KEY_Init();
    
    //����һ��IWDG���Գ���
    OLED_ShowString(1,1,"Test IWDG");
    
    //��λ���жϸ�λԭ��
    if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET )//�Ƕ������Ź���λ
    {
        OLED_ShowString(2,1,"IWDG RST");
        //����������Ź���λ��־λ���������λҲ�����Զ��������Ҫ�ֶ���
        RCC_ClearFlag();
    }
    else
    {
        OLED_ShowString(2,1,"     RST");
    }
    
    
    //���ö������Ź�
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//д��0x5555�رձ���
    IWDG_SetPrescaler(IWDG_Prescaler_16);//����16��Ƶ���������ʱ���Ϊ0.025*16*4096 = 1638ms��
    IWDG_SetReload(2500 - 1);//������װֵΪ2500 ����ι��ʱ�����1s���ˡ�
    IWDG_ReloadCounter();//����ǰι��һ�Σ������¼�����
    IWDG_Enable(); //����С��
    
    while(1)
    {
        KEY_Get();
        
        
        //0.9sι��һ��
        Delay_ms(200);
        IWDG_ReloadCounter();
        OLED_ShowString(3,1,"WangWang");//��ʾι����
        Delay_ms(700);
        OLED_ShowString(3,1,"        ");//��˸
    }
}
//�������»����while�������򣬲���ι��
//uint8_t KEY_Get(void)
//{
//    if(KEY1)
//    {
//        Delay_ms(10);
//        while(KEY1);//�ȴ��ɿ�
//            return 1;
//    }
//    return 0;
//}


