#include "stm32f10x.h"                  // Device header

//引脚为A2  

//计次变量
uint16_t CountSensor_Count = 0;

//初始化
void CountSensor_Init(void)
{
    //开启A2的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //开启挂载在APB2外设的AFIO外设时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    //EXTI时钟和NVIC的时钟不用手动打开。
    
    //配置GPIO
    GPIO_InitTypeDef GPIO_InitStructrue;
    GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_IPU;        //上拉输入模式
    GPIO_InitStructrue.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_50MHz;    
    GPIO_Init(GPIOA,&GPIO_InitStructrue);
    
    //配置AFIO （F1中在GPIO.h文件中）（目的是为了把GPIOA的PIN2引脚映射到AFIO中。）
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2);//这里需要根据PIn和GPIOx来选择

    
    //配置EXTI
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;          //选择中断线路，这里是PIN2 所以为2   
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;           //是否使能指定的中断线路
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //中断或响应模式   
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//上升或下降或边沿触发
    EXTI_Init(&EXTI_InitStructure);
    
    //配置NVIC（因为NVIC属于内核，所以被分配到内核的杂项中去了，在misc.c）
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置抢占和响应优先级
     
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;       //在stm32f10x.h文件里。让你找IRQn_Type里的一个中断通道。这里使用的是md的芯片（如果引脚是15-10或者9-5则需要去找对应的那个）这里我是PIN2.所以找2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //是否使能指定的中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//抢占优先级（这里可以看表。看范围，）
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;       //指定响应优先级
    NVIC_Init(&NVIC_InitStructure);    
    
   
    
}



//获取当前的计数
uint16_t CountSenSor_Get(void)
{
    return CountSensor_Count;
}


//在STM32中，中断的函数都是固定的。他们在启动文件中存放xxx.s 
//以IRQHandler结尾的就是中断函数的名字。
//在这里需要找到对应的中断函数，我这里是2
void EXTI2_IRQHandler(void)//中断函数是无参无返回值的。中断函数必须写对，写错就进不去
{
    //在进入中断后，一般要判断一下这个是不是我们想要的那个中断源触发的中断。
    //但是在这里。我是GPIOA的PIN2引脚，所以不用写。
    //如果是5-9 10-15的引脚。他们EXTI到NVIC是几个共用的。
    //所以需要根据EXTI输入时的16根引脚。来判断是16根引脚的那一根发送的中断请求。
    //这里规范写的话需要加上去
    //查找标志位函数在exit.h中。
    if(EXTI_GetITStatus(EXTI_Line2) == SET)//第一个参数是行数.判断这个线的标志位是不是== SET。是则是我们想要的
    {
    
        CountSensor_Count++;
        EXTI_ClearITPendingBit(EXTI_Line2);//中断结束后，要调用清除标志位的函数。如果你不清除，程序会一直进入中断
    }
}















