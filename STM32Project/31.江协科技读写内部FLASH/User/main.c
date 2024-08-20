#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Store.h"
#include "Key.h"

int main(void)
{
    /*模块初始化*/
    OLED_Init();                //OLED初始化
    KEY_Init();                //按键初始化
    Store_Init();               //参数存储模块初始化，在上电的时候将闪存的数据加载回Store_Data，实现掉电不丢失
    
    /*显示静态字符串*/
    OLED_ShowString(1, 1, "Flag:");
    OLED_ShowString(2, 1, "Data:");
    
    while (1)
    {
        uint8_t Key_Num = KEY_Get();    //记录按下的键   
        if (Key_Num == 1)               //按键1按下
        {
            Store_Data[1] ++;           //变换测试数据
            Store_Data[2] += 2;
            Store_Data[3] += 3;
            Store_Data[4] += 4;
            Store_Save();               //将Store_Data的数据备份保存到闪存，实现掉电不丢失
        }
        
        else if (Key_Num == 2)          //按键2按下
        {
            Store_Clear();              //将Store_Data的数据全部清0
        }
        
        OLED_ShowHexNum(1, 6, Store_Data[0], 4);    //显示Store_Data的第一位标志位
        
        OLED_ShowHexNum(3, 1, Store_Data[1], 4);    //显示Store_Data的有效存储数据
        OLED_ShowHexNum(3, 6, Store_Data[2], 4);
        OLED_ShowHexNum(4, 1, Store_Data[3], 4);
        OLED_ShowHexNum(4, 6, Store_Data[4], 4);
    }
}
