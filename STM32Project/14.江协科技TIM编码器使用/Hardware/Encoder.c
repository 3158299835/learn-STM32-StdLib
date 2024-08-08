#include "stm32f10x.h"                  // Device header

void Encoder_Init(void)
{
    //开启GPIOA和定时器外设的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    
    //配置PA6、PA7
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    
    //编码器会托管时钟，这里不需要配置输入时钟
    
    //配置时基单元 
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//滤波器分频设置F N
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//计数模式没用，会被编码器托管
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1; //一般选择满量程计数，这样在从0-1就会变成65535.后续强制把65536转换为有符号数，就可以把他转换为负数。
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;//不分频
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
    
    //配置输入捕获单元的滤波器和边缘极性选择
    //其余的交给初始化函数
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);//初始化结构体
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//通道为1
    TIM_ICInitStructure.TIM_ICFilter = 0XF;//滤波器为0xF
    TIM_ICInit(TIM3,&TIM_ICInitStructure);
    
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;//通道为2
    TIM_ICInitStructure.TIM_ICFilter = 0XF;//滤波器为0xF
    TIM_ICInit(TIM3,&TIM_ICInitStructure);
    
    //下边这一句在编码器里配置有，不需要配置）
//    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//上升沿 也就是高低电平记性不翻转  高电平有效
//    TIM_ICInitStructure.TIM_ICPrescaler = ;  这两句没作用了
//    TIM_ICInitStructure.TIM_ICSelection = ;  这两句没作用了

    //通道2的滤波器配置

    
    
    //配置编码器接口  选择TI12 都计数       是否反向？
    TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
    
    TIM_Cmd(TIM3,ENABLE);
    
    
    
}




//读取编码器的值
//读完后清零CNT
int16_t Encoder_Get(void)
{
    int16_t Temp = TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3,0);//清零
    return Temp;
}






