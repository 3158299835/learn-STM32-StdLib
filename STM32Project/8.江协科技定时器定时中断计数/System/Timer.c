#include "stm32f10x.h"                  // Device header

extern uint16_t Num;//记录时间的变量、这里是引用了main.c里的Num来控制。

void Timer_Init(void)
{
    //开启RCC时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//TIM2是挂载在APB1总线上的
    //选择时基单元钟源为内部时钟。在tim.h头文件
    TIM_InternalClockConfig(TIM2);
    //配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//初始化时基单元要定义的结构体
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//指定时钟分频、1分频
    //这里的分频是为了给滤波器采样频率f  采样点数N f越低、N越多。采样点数越好。
    //但信号延迟越大。f可以有内部时钟直接而来，也可以由分频器分频的到。
    //这里的分频器就是对送往滤波器的f的分频器进行控制。在这里直接用1就好，和时基单元关系不大
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//选择计数模式，分别是向上、向下、三种中央对其模式
    TIM_TimeBaseStructure.TIM_Period = 10000 - 1;//ARR重装值  =  值 +1   所以我们再用的时候要-1.才能正确匹配。这里是ARR和PSC定时1s
    TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1;//PSC分频器分频系数= 值+1
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//重复计数器，这个是高级计数器才有的，我们不需要。所以给0
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//这个函数是初始化时基单元的。
    /*程序在运行TIM_TimeBaseInit 函数时，会在最后一步手动更新一下更新事件。因为
    计时器和ARR重装寄存器。他们都有一个 影子寄存器  因为影子寄存器的存在。我们写入的值（重装寄存器ARR和计数器的值CNT）不会立刻生效，而是等待此次周期结束，也就是在更新事件的时候才会生效。所以这个函数在最后的时候，手动生成了一下更新事件。
    但副作用是，更新事件和更新中断是同时发生作用的。所以此时的中断标志位已经置一了。（中断标志位 不手动清除会一直为1）。所以当程序起来之后，会立马进入中断一次。
    所以在上电复位之后，在查看计数器时已经是1了）
    所以在这里我们需要手动的先清除一下此次的更新中断标志位*/
    TIM_ClearFlag(TIM2,TIM_IT_Update);          //清除更新标志位
    //配置输出中断控制
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能TIM2的更新中断到NVIC
    //配置NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//选择分组
    NVIC_InitTypeDef NVIC_InitStructuer;//定义结构体
    NVIC_InitStructuer.NVIC_IRQChannel = TIM2_IRQn;//选择定时器2在NVIC里的通道
    NVIC_InitStructuer.NVIC_IRQChannelCmd = ENABLE;//是否使能
    NVIC_InitStructuer.NVIC_IRQChannelPreemptionPriority = 2;//抢占优先级
    NVIC_InitStructuer.NVIC_IRQChannelSubPriority = 2;//响应优先级。
    NVIC_Init(&NVIC_InitStructuer);
    //运行控制，使能计数器
    TIM_Cmd(TIM2,ENABLE);
}




//配置中断函数
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)//检查中断标志位
    {
        Num++;
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}


