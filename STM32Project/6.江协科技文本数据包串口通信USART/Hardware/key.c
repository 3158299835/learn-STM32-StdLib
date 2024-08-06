#include "key.h"
#include "stm32f10x.h"

//初始化GPIO
//按键1 2是低电平检测。所以模式配置为上拉输入
void KEY_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能APB2总线的GPIOC 时钟
    
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_0;//KEY 1  2 对应引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);//初始化GPIOB 11  0引脚
    
}




//按键检测
uint8_t KEY_Scan(uint8_t mode)
{
    static uint8_t Key_up = 1;//初始化keyup = 1，未被按下
    if(mode == 1)
    {
        Key_up = 1;//如果启动了连续按下模式，那么就强制定义上一次状态为未被按下
    }
    if(Key_up && (KEY1||KEY2))//上一次未被按下，现在KEY1或2按下。那么就有效
    {
        Delay_ms(10);//去抖动
        Key_up = 0;//赋值为0,标记按下
        if     (KEY1)
        {
            return 1;
        }
        else if(KEY2)
        {
            return 2;
        }    
        }
    else if(KEY1 == 0 && KEY2 == 0)
    {
        Key_up = 1;//未被按下，那么赋值为1，标记未被按下。
    }
    return 0;
}
