#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"//直接拿的延时函数
int main()
{

    
    LED_Init();//初始化LED


    while(1)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_15);//PB15为高电平，熄灭
        GPIO_ResetBits(GPIOB,GPIO_Pin_12);//PB12为低电平，点亮
        Delay_ms(500);//延时500ms
        GPIO_SetBits(GPIOB,GPIO_Pin_12);//PB12为高电平，熄灭
        GPIO_ResetBits(GPIOB,GPIO_Pin_13);//PB13为低电平，点亮
        Delay_ms(500);//延时500ms
        GPIO_SetBits(GPIOB,GPIO_Pin_13);//PB13为高电平，熄灭
        GPIO_ResetBits(GPIOB,GPIO_Pin_14);//PB14为低电平，点亮
        Delay_ms(500);//延时500ms
        GPIO_SetBits(GPIOB,GPIO_Pin_14);//PB14为高电平，熄灭
        GPIO_ResetBits(GPIOB,GPIO_Pin_15);//PB15为低电平，点亮
        Delay_ms(500);//延时500ms
    }
}
