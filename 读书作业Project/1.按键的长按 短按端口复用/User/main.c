#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "delay.h"
#include "Key.h"
#include "Serial.h"
#include "oled.h"
int main()
{

    KEY_Init();//初始化KEY
    LED_Init();//初始化LED
    Delay_Init();//初始化延时函数
    OLED_Init();//初始化OLED;
    Serial_Init();//初始化串口


    OLED_ShowString(1,4,"ing");//在while循环外显示ing
    
    uint16_t num = 0;
    while(1)
    {
       
         if(KEY1 == 1)//按键1按下
         {
            Delay_ms(10);//消抖
            if(KEY1 == 1)//确实按下了。
            {
                 OLED_Clear();//清屏 如果松开按钮后  显示ing 就代表已经被复位
                while(KEY1 == 1)//等待松开
                {
                    Delay_ms(10);
                    num++;
                    OLED_ShowNum(1,1,num,4);
                }
                if(num <= 0)
                {
                    ;
                }
                else if(num >= 300)//代表按了三秒
                {
                    num = 0;
                    __set_FAULTMASK(1);     //全局中断禁止
                    NVIC_SystemReset();     //软复位
                }
                else
                {
                    num = 0;
                    LED_Flip(1);
                }
            }
         
         }
    }
}




