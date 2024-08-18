#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void KEY_Init(void)
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    Delay_Init();
    
}

uint8_t KEY_Get(void)
{
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == RESET)
    {
        Delay_ms(10);
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == RESET)
        {
            while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == RESET);
            return 1;
        }
    }
    return 0;
}
