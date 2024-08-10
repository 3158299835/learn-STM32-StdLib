#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
/*
    ���ڿ��Ź����Գ���
    ��ʱʱ��50ms
    ����ʱ��30ms

*/

int main()
{
    OLED_Init();//��ʼ��OLED;
    KEY_Init();
    
    //����һ��WWDG���Գ���
    OLED_ShowString(1,1,"Test WWDG");
    
    //��λ���жϸ�λԭ��
    if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET )//�Ƕ������Ź���λ
    {
        OLED_ShowString(2,1,"WWDG RST");
        //������ڿ��Ź���λ��־λ���������λҲ�����Զ��������Ҫ�ֶ���
        RCC_ClearFlag();
    }
    else
    {
        OLED_ShowString(2,1,"     RST");
    }
    /*
        ���ȵõ�ʱ��ʱ�䡣32M * 1/4096 = 7812.5HZ
        ��ô��һ�����ڵ�ʱ�����0.000128s
        ��ôѡ���ƵΪ3��Ҳ����2^3 = 8��Ƶ����ô����һ�����ڵ�ʱ����� 0.000128 * 8= 0.001024s
        ��ʱ�������װ�ؼĴ���ѡΪ������֣�6λ��63 + 1
        ��ô�������ʱʱ�����0.58s
        Ҳ�������ֵΪ58ms
        ����Ҫ���õ�50ms�ڷ�Χ��
        ��ô����Ҫ���õķ�Ƶϵ������ 3 ����õ���װֵӦ�ǣ�Լ���ڣ�55��ʵ�ʸ�54  ����Ϊ - 1��
    
        ���㴰��ʱ�䣬����Ϊ30ms  ��ô���ô��ڵ�6λ��ֵΪ
        30 = 1/32m * 4096 * 8 *(54 - W[5:0])
        ���W��ֵΪ 21
      
    */
    //���ô��ڿ��Ź�
    //�������ڿ��Ź�ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
    WWDG_SetPrescaler(WWDG_Prescaler_8);
    WWDG_SetWindowValue(0x40 | 21);//30ms 
    WWDG_Enable(0x40 | 54);
    // 50ms �����0x40��Ϊ�˰Ѽ������ĵ���λ��1 
    // ��Ϊ������Ϊ0�����ɸ�λ�źš�����Ҳ����װ����Ҫ -1 ��ԭ��
    uint32_t i = 0;
    while(1)
    {
        KEY_Get();
        
        OLED_ShowString(3,1,"Wang");//����֣��������ʾWangWang�Ͳ�����....����ʾ�����ַ��ѵ���ô�˷�ʱ����
        Delay_ms(20);
        OLED_ShowString(3,1,"    ");
        Delay_ms(20);
        OLED_ShowNum(4,1,i,4);
        i++;
        WWDG_SetCounter(0x40 | 54);//ι��������ע�ⲻҪ��ʹ��ʱι��̫����

       
        
        
    }
}

