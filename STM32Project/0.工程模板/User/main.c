#include "stm32f10x.h"                  // Device header

int main()
{
    //寄存器点灯
//    RCC->APB2ENR = 0x00000010;//打开GPIOC的时钟
//    GPIOC->CRH = 0x00300000;//配置PC13口为推挽输出模式，速度为50MHz
//    GPIOC->ODR = 0x00000000;//配置PC13口为高电平
    //库函数点灯
    
    //打开GPIOC的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    //配置PC13的端口为推挽输出模式，速度为50MHz
    GPIO_InitTypeDef GPIO_InitStructure;                //定义GPIO_Init的第二个参数：结构体变量
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOC,&GPIO_InitStructure);//GPIO_Init，配置GPIO模式
    
    //设置PC 13为低电平。点灯。
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
    //GPIO_SetBits(GPIOC,GPIO_Pin_13);
    
    while(1)
    {
    
    
    
    }
}
