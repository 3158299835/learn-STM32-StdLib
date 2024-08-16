#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
#include "W25Q64.h"

/**
  * 函    数：验证SPI控制W25Q64存储器
  * 参    数：无
  * 返 回 值：无
  * 注意事项：无
  */

uint8_t ArrWrite[] = {0xAA, 0xBB, 0xCC, 0xDD};
uint8_t ArrRead[4];

int main()
{
    Delay_Init();//初始化演示
    OLED_Init();//初始化OLED;
    W25Q64_Init();//初始化W25Q64存储器

    OLED_ShowString(1,1,"MID:  ,DID:   ");
    
    W25Q64_ReadID(&W25Q64_ID);//读ID放到这个结构体中
    OLED_ShowHexNum(1,5,W25Q64_ID.MID,2);
    OLED_ShowHexNum(1,12,W25Q64_ID.DID,4);//显示MID DID
    
    OLED_ShowString(2,1,"W:");
    OLED_ShowString(3,1,"R:");
    
    W25Q64_PageErase(0x000000);               //擦除地址。写入前需要（最好定位到扇区的起始地址（后三位为0））
    W25Q64_PageProgram(0x000000,ArrWrite,4);  //写入数组中数据到存储器
    W25Q64_ReadData(0x000000,ArrRead,4);      //读取存储器中数据到数组
    
    OLED_ShowHexNum(2, 3, ArrWrite[0], 2);
    OLED_ShowHexNum(2 ,6, ArrWrite[1], 2);
    OLED_ShowHexNum(2, 9, ArrWrite[2], 2);
    OLED_ShowHexNum(2, 12, ArrWrite[3], 2);
    
    OLED_ShowHexNum(3, 3, ArrRead[0], 2);
    OLED_ShowHexNum(3 ,6, ArrRead[1], 2);
    OLED_ShowHexNum(3, 9, ArrRead[2], 2);
    OLED_ShowHexNum(3, 12, ArrRead[3], 2);




    while(1)
    {

    }
}



