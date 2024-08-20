#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Store.h"

int main(void)
{   
    //0x1FFFF7E0为FLASH ID 寄存器位置，。是一个96位的
    
    OLED_Init();                        //OLED初始化
    
    OLED_ShowString(1, 1, "F_SIZE:");   //显示容量：
    
    OLED_ShowHexNum(1, 8, *((__IO uint16_t *)(0x1FFFF7E0)), 4);     //使用指针读取指定地址下的 闪存容量寄存器
    
    OLED_ShowString(2, 1, "U_ID:");     //显示芯片ID：
    
    //使用指针读取指定地址下的产品唯一身份标识寄存器
    //可以由字节、半字、字的方式读取
    OLED_ShowHexNum(2, 6, *((__IO uint8_t *)(0x1FFFF7E8)), 2);              //字节读出：第一个字节        （0-8位）
    OLED_ShowHexNum(2, 9, *((__IO uint8_t *)(0x1FFFF7E8) + 1), 2);          //字节读出：第二个字节        （9-16位）
    OLED_ShowHexNum(2, 12, *((__IO uint16_t *)(0x1FFFF7E8) + 1), 4);        //半字读出：第3 、4 个字节    （16-32位）
    OLED_ShowHexNum(3, 1, *((__IO uint32_t *)(0x1FFFF7E8 + 1)), 8);      //字  读出：5 6 7 8个字节     （33-64位）
    OLED_ShowHexNum(4, 1, *((__IO uint32_t *)(0x1FFFF7E8 + 2)), 8);      //字  读出：9 10 11 12个字节  （64-96位）
    
    while (1)
    {

    }
}
