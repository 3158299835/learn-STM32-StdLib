#include "delay.h"

// 定义延时计数值
static volatile uint32_t TimingDelay;

// 延时函数初始化
void Delay_Init(void)
{
    // 配置 SysTick 为 1us 中断一次
    if (SysTick_Config(SystemCoreClock / 1000000))
    {
        while (1);  // 配置错误，进入死循环
    }
}

// 延时函数
void Delay_us(uint32_t us)
{
    TimingDelay = us;
    while (TimingDelay!= 0);
}

// SysTick 中断处理函数
void SysTick_Handler(void)
{
    if (TimingDelay!= 0)
    {
        TimingDelay--;
    }
}

// 毫秒级延时函数
void Delay_ms(uint32_t ms)
{
    Delay_us(ms * 1000);
}
