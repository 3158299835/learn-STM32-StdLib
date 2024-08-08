#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
#include "Encoder.h"
#include "Timer.h"

/*
    使用PA6 和 PA7 引脚的复用模式
    也就是TIM3 的CH1通道和CH2通道
    使用编码器接口
*/
int16_t Speed = 0;//对Timer.c中声明过的变量 

int main(){
    OLED_Init();//初始化OLED;
    Encoder_Init();//初始化Encoder
//    Delay_Init();//初始化延时函数
    
    Timer_Init();//初始化定时1s中断函数
    

    
    
    OLED_ShowString(1,1,"Num:");
    while(1)
    {
        OLED_ShowSignedNum(1,5,Speed,5);
//        Delay_ms(1000);
        
    }

}
    

