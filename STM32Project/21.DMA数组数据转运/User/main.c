#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
#include "MyDMA.h"
/*



*/

uint8_t DataA[] = { 0x01, 0x02, 0x03, 0x04 };
uint8_t DataB[4] = { 0 };


int main()
{
    OLED_Init();//初始化OLED;
    Delay_Init();//初始化延时
    
    MyDMA_Init((uint32_t)DataA,(uint32_t)DataB,4);//初始化DMA
    
    
    //显示地址
    OLED_ShowString(1,1,"DataA");
    OLED_ShowHexNum(1, 1, (uint32_t)&DataA, 8);
    
    OLED_ShowString(3,3,"DataB");
    OLED_ShowHexNum(3, 1, (uint32_t)&DataB, 8);

    while(1)
    {
        //显示DataA数据
        OLED_ShowHexNum(2, 1, DataA[0], 2);
        OLED_ShowHexNum(2, 4, DataA[1], 2);
        OLED_ShowHexNum(2, 7, DataA[2], 2);
        OLED_ShowHexNum(2, 10, DataA[3], 2);
        //延时
        Delay_ms(1000);
        
        //传输
        MyDMA_Transfer();
        
        //显示DataB数据
        OLED_ShowHexNum(4, 1, DataB[0], 2);
        OLED_ShowHexNum(4, 4, DataB[1], 2);
        OLED_ShowHexNum(4, 7, DataB[2], 2);
        OLED_ShowHexNum(4, 10, DataB[3], 2);
        //延时
        Delay_ms(1000);
        //源数组自增
        DataA[0]++;
        DataA[1]++;
        DataA[2]++;
        DataA[3]++;        
    }
}

//uint8_t SRAM = 0x66;
//const uint8_t Flash = 0x77;
//int main()
//{
//    OLED_Init();//初始化OLED;
//    OLED_ShowHexNum(1,1,SRAM,2);
//    OLED_ShowHexNum(1,4,(uint32_t)&SRAM,8);//地址是0x2000 0000 开头的。位于RAM类型的运行内存SRAM中
//    OLED_ShowHexNum(2,1,Flash,2); 
//    OLED_ShowHexNum(2,4,(uint32_t)&Flash,8);//地址是0x0800 0000 开头的。位于Flash中，是只读的。放到flash可以节省空间
//    OLED_ShowHexNum(3,4,(uint32_t)&ADC1->DR, 8); //ADC_DR寄存器是外设。所以在RAM类型的 0x4000 0000上。这个地址是固定的。
//    while(1)
//    {
//    }
//}



