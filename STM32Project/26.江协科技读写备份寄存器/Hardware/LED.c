#include "stm32f10x.h"

void LED_Init(void)
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;                

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    
    GPIO_SetBits(GPIOB,GPIO_Pin_12);
    GPIO_SetBits(GPIOB,GPIO_Pin_13);//设置GPIO为高电平。LED为熄灭

}

void LED_ON(uint8_t num)
{
    switch(num)
    {
        case 1 : GPIO_ResetBits(GPIOB,GPIO_Pin_12);break;
        case 2 : GPIO_ResetBits(GPIOB,GPIO_Pin_13);break;
        default : ;
    }
}

void LED_OFF(uint8_t num)
{
    switch(num)
    {
        case 1 : GPIO_SetBits(GPIOB,GPIO_Pin_12);break;
        case 2 : GPIO_SetBits(GPIOB,GPIO_Pin_13);break;
        default : ;
    }
}
