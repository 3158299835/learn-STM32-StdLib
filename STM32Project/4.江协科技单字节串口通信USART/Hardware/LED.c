#include "led.h"


//初始化LED
void LED_Init(void)
{
    //跑马灯引脚为PB 12 13 14 15,LED为低电平有效
    
        
    //F4的芯片在这里还需要配置上下拉电阻PuPd 以及 推挽或者开漏Otype
    
    //打开GPIOB的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    //定义GPIO_Init的第二个参数：结构体变量
    GPIO_InitTypeDef GPIO_InitStructure;                
    //↑在C99下不需要放到第第一行
    
    
    //下面的GPIO是分开配置的，其实可以写成A||B.这样就不用写那么多次了。这里我就不改了
    
    
    //PB12
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //配置PC13的端口为推挽输出模式，速度为50MHz
    
    GPIO_Init(GPIOB,&GPIO_InitStructure);//GPIO_Init，初始化GPIO B，PB12的GPIO
    GPIO_SetBits(GPIOB,GPIO_Pin_12);//设置GPIO为高电平。LED为熄灭
    //
    
   //PB13
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_13);
    
   //PB14
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_14);
    
    
   //PB15
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_15);
    
}


//熄灭LED
void LED_OFF(uint8_t num)
{
    if(num == 0)
    {
        return;
    }
    if(num == 1)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_12);
    }
    else if(num == 2)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_13);
    }
    else if(num == 3)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_14);
    }
    else if(num == 4)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_15);
    }
}

//点亮LED
void LED_ON(uint8_t num)
{
    if(num == 0)
    {
        return;
    }
    if(num == 1)
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_12);
    }
    else if(num == 2)
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_13);
    }
    else if(num == 3)
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_14);
    }
    else if(num == 4)
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_15);
    }
}

//反转LED
void LED_Flip(uint8_t num)
{
    if(num == 0)
    {
        return;
    }
    else if(num == 1)
    {
        if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12) == Bit_SET)
        {
            GPIO_ResetBits(GPIOB,GPIO_Pin_12);
        }
        else
        {
            GPIO_SetBits(GPIOB,GPIO_Pin_12);
        }
    }
    else if(num == 2)
    {
        if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_13) == Bit_SET)
        {
            GPIO_ResetBits(GPIOB,GPIO_Pin_13);
        }
        else
        {
            GPIO_SetBits(GPIOB,GPIO_Pin_13);
        }
    }
    else if(num == 3)
    {
        if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_14) == Bit_SET)
        {
            GPIO_ResetBits(GPIOB,GPIO_Pin_14);
        }
        else
        {
            GPIO_SetBits(GPIOB,GPIO_Pin_14);
        }
    }
    else if(num == 4)
    {
        if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_15) == Bit_SET)
        {
            GPIO_ResetBits(GPIOB,GPIO_Pin_15);
        }
        else
        {
            GPIO_SetBits(GPIOB,GPIO_Pin_15);
        }
    }
}
