#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"

int main(void)
{
    /*模块初始化*/
    OLED_Init();        //OLED初始化
    MyRTC_Init();       //RTC初始化
    
    /*显示静态字符串*/
    OLED_ShowString(1, 1, "CNT:");  //时间戳计数器
    OLED_ShowString(2, 1, "ALR:");  //闹钟值
    OLED_ShowString(3, 1, "ALRF:"); //闹钟标志位
    
    //存下要显示的闹钟值（闹钟寄存器只可写不可读，所以要存下，方便显示）
    uint32_t Alarm = RTC_GetCounter() + 10;
    //设定闹钟为十秒后
    RTC_SetAlarm(Alarm);
    //显示闹钟
    OLED_ShowNum(2, 5, Alarm, 10);
    
    //开启PWR时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    
    while (1)
    {
        OLED_ShowNum(1, 5, RTC_GetCounter(), 10);                   //显示32位的秒计数器
        OLED_ShowNum(3, 6, RTC_GetFlagStatus(RTC_FLAG_ALR), 1);     //显示32位的秒计数器
        
        OLED_ShowString(4,1,"Running");
        Delay_ms(100);
        OLED_ShowString(4,1,"       ");
        Delay_ms(100);
        
        //在进入待机模式之前，一般都需要把所有的外设 都关闭，比如屏幕、电机等等。
        //这里清个屏表示一下
        OLED_Clear();

        
        PWR_EnterSTANDBYMode();//进入待机模式
    }
}
