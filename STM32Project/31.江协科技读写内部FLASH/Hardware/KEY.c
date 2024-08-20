#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define KEY1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == RESET
#define KEY2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) == RESET

void KEY_Init(void)
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    
}

uint8_t KEY_Get(void)
{
    if(KEY1 | KEY2)
    {
        Delay_ms(10);
        if(KEY1)
        {
            while(KEY1);
            return 1;
        }
        else if(KEY2)
        {
            while(KEY2);
            return 2;
        }
    }
    return 0;
}
