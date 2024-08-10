#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
/*
    独立看门狗测试程序
    喂狗时间为1s内

*/

int main()
{
    OLED_Init();//初始化OLED;
    Delay_Init();
    KEY_Init();
    
    //这是一个IWDG测试程序
    OLED_ShowString(1,1,"Test IWDG");
    
    //复位后判断复位原因
    if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET )//是独立看门狗复位
    {
        OLED_ShowString(2,1,"IWDG RST");
        //清除独立看门狗复位标志位，这个他复位也不会自动清除，需要手动清
        RCC_ClearFlag();
    }
    else
    {
        OLED_ShowString(2,1,"     RST");
    }
    
    
    //配置独立看门狗
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//写入0x5555关闭保护
    IWDG_SetPrescaler(IWDG_Prescaler_16);//设置16分频（这样最大时间才为0.025*16*4096 = 1638ms）
    IWDG_SetReload(2500 - 1);//设置重装值为2500 这样喂狗时间就是1s内了。
    IWDG_ReloadCounter();//启动前喂狗一次，重置下计数器
    IWDG_Enable(); //启动小狗
    
    while(1)
    {
        KEY_Get();
        
        
        //0.9s喂狗一次
        Delay_ms(200);
        IWDG_ReloadCounter();
        OLED_ShowString(3,1,"WangWang");//显示喂狗了
        Delay_ms(700);
        OLED_ShowString(3,1,"        ");//闪烁
    }
}
//按键按下会进入while阻塞程序，不让喂狗
//uint8_t KEY_Get(void)
//{
//    if(KEY1)
//    {
//        Delay_ms(10);
//        while(KEY1);//等待松开
//            return 1;
//    }
//    return 0;
//}


