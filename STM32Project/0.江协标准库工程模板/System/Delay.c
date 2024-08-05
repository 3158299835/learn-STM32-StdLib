#include "delay.h"

// ������ʱ����ֵ
static volatile uint32_t TimingDelay;

// ��ʱ������ʼ��
void Delay_Init(void)
{
    // ���� SysTick Ϊ 1us �ж�һ��
    if (SysTick_Config(SystemCoreClock / 1000000))
    {
        while (1);  // ���ô��󣬽�����ѭ��
    }
}

// ��ʱ����
void Delay_us(uint32_t us)
{
    TimingDelay = us;
    while (TimingDelay!= 0);
}

// SysTick �жϴ�����
void SysTick_Handler(void)
{
    if (TimingDelay!= 0)
    {
        TimingDelay--;
    }
}

// ���뼶��ʱ����
void Delay_ms(uint32_t ms)
{
    Delay_us(ms * 1000);
}
