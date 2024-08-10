#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
/*
    窗口看门狗测试程序
    超时时间50ms
    窗口时间30ms

*/

int main()
{
    OLED_Init();//初始化OLED;
    KEY_Init();
    
    //这是一个WWDG测试程序
    OLED_ShowString(1,1,"Test WWDG");
    
    //复位后判断复位原因
    if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET )//是独立看门狗复位
    {
        OLED_ShowString(2,1,"WWDG RST");
        //清除窗口看门狗复位标志位，这个他复位也不会自动清除，需要手动清
        RCC_ClearFlag();
    }
    else
    {
        OLED_ShowString(2,1,"     RST");
    }
    /*
        首先得到时钟时间。32M * 1/4096 = 7812.5HZ
        那么他一个周期的时间就是0.000128s
        那么选择分频为3，也就是2^3 = 8分频。那么现在一个周期的时间就是 0.000128 * 8= 0.001024s
        这时候如果重装载寄存器选为最大数字（6位）63 + 1
        那么他的最大超时时间就是0.58s
        也就是最大值为58ms
        我们要设置的50ms在范围内
        那么我们要设置的分频系数就是 3 所求得的重装值应是（约等于）55。实际给54  （因为 - 1）
    
        计算窗口时间，设置为30ms  那么设置窗口的6位的值为
        30 = 1/32m * 4096 * 8 *(54 - W[5:0])
        求得W的值为 21
      
    */
    //配置窗口看门狗
    //开启窗口开门狗时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
    WWDG_SetPrescaler(WWDG_Prescaler_8);
    WWDG_SetWindowValue(0x40 | 21);//30ms 
    WWDG_Enable(0x40 | 54);
    // 50ms 这里的0x40是为了把计数器的第七位置1 
    // 因为当他减为0是生成复位信号。（这也是重装载需要 -1 的原因）
    uint32_t i = 0;
    while(1)
    {
        KEY_Get();
        
        OLED_ShowString(3,1,"Wang");//很奇怪，如果是显示WangWang就不行了....多显示几个字符难道这么浪费时间吗
        Delay_ms(20);
        OLED_ShowString(3,1,"    ");
        Delay_ms(20);
        OLED_ShowNum(4,1,i,4);
        i++;
        WWDG_SetCounter(0x40 | 54);//喂狗，这里注意不要离使能时喂狗太近。

       
        
        
    }
}

