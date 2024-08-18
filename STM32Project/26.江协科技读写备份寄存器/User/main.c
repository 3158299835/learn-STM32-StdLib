#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "Key.h"


/**
  * 函    数：STM32 BKP备份寄存器的读写测试
  * 参    数：无
  * 返 回 值：无
  * 注意事项：无
  */
  
uint16_t WriteArr[] = {0x0000, 0x0001};
uint16_t ReadArr[2] = { 0 };
  
int main()
{
    OLED_Init();//初始化OLED;
    KEY_Init();//初始化按键
    
    //使能时钟电源和后备接口时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
    
    //使能备份访问控制
    PWR_BackupAccessCmd(ENABLE);
    
    OLED_ShowString(1,1,"W:");
    OLED_ShowString(2,1,"R:");
    while(1)
    {
        if(KEY_Get() == 1)
        {
            //写入BKP
            BKP_WriteBackupRegister(BKP_DR1,WriteArr[0]);
            BKP_WriteBackupRegister(BKP_DR2,WriteArr[1]);
            
            //显示写入的值
            OLED_ShowHexNum(1,3,WriteArr[0],4);
            OLED_ShowHexNum(1,8,WriteArr[1],4);
            
            WriteArr[0]++;
            WriteArr[1]++;
        }
        //读取BKP
        ReadArr[0] = BKP_ReadBackupRegister(BKP_DR1);
        ReadArr[1] = BKP_ReadBackupRegister(BKP_DR2);
        //显示读取的值
        OLED_ShowHexNum(2,3,ReadArr[0],4);
        OLED_ShowHexNum(2,8,ReadArr[1],4);
        
    }
}



