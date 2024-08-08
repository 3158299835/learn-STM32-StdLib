#include "stm32f10x.h"                  // Device header




//初始化
void IC_Init(void)
{
   /*
        配置TIm3的通道1引脚（PA6）读取信号
    */
    
    //使能PA0输出引脚
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//PA6
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    //使能时钟外设
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    
    //选择TIM2为内部时钟，若不调用此函数，TIM默认也为内部时钟
    TIM_InternalClockConfig(TIM3);
    
    //配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;\
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//指定滤波器采样频率F和采样点数N为 模式1
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;//决定了CNT计数的最大值，测频率最好要设置大一些，防止计数溢出
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;//决定了测周法的标准频率fc，暂时先定义为1MHZ
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//高级定时器的复用定时器
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
    
    //清除时基单元配置好后产生的标志位
    TIM_ClearFlag(TIM3,TIM_IT_Update);
    
    //配置通道一
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//选择通道1
    TIM_ICInitStructure.TIM_ICFilter = 0xF;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//上升沿有效
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//触发信号分频器
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//直接输入
    TIM_ICInit(TIM3,&TIM_ICInitStructure);
    
    //方法二（PWMI函数）和方法一等同。 会进行判断然后帮你弄成相反的（可以看F2）
    //（只支持通道1 和通道2 的配置，不能传入通道3 4）
    TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);
//    //配置通道二（方法一，复制一份）
//    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;//选择通道2
//    TIM_ICInitStructure.TIM_ICFilter = 0xF;
//    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;//下降沿有效
//    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//触发信号分频器
//    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;//交叉输入
//    TIM_ICInit(TIM3,&TIM_ICInitStructure);
    
    //配置主从模式的TRGI的触发源为TI1FP1
    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
    
    //配置从模式为reset
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);//读取后自动清除
    
    //使能定时器
    TIM_Cmd(TIM3,ENABLE);
}


//获取频率
uint32_t IC_GetFreq(void)
{
    //执行公式，fx = fc / N  fc = 1M
    return 1000000 / (TIM_GetCapture1(TIM3)+1);//读取TIM3的通道1的CCR的值
    // +1 为面向对象编程...因为1000HZ显示的是1001
    //+1 的原因是因为每次都会少记录一个。+1补成999+1 这样就能整除了
}



//获取占空比
uint32_t IC_GetButy(void)
{
    //下降沿的计数 比上 上升沿计数就是占空比
    //下降沿记得数存在通道二的CCR2中，上升沿记得数存在CCR1中。
    return (TIM_GetCapture2(TIM3) + 1 ) * 100 / (TIM_GetCapture1(TIM3) + 1);//*100是现实整数 1%~100%
    //CCR总会少一个数，所以面向对象编程

}


