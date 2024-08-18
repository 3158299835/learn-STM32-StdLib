#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "Key.h"


/**
  * ��    ����STM32 BKP���ݼĴ����Ķ�д����
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */
  
uint16_t WriteArr[] = {0x0000, 0x0001};
uint16_t ReadArr[2] = { 0 };
  
int main()
{
    OLED_Init();//��ʼ��OLED;
    KEY_Init();//��ʼ������
    
    //ʹ��ʱ�ӵ�Դ�ͺ󱸽ӿ�ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
    
    //ʹ�ܱ��ݷ��ʿ���
    PWR_BackupAccessCmd(ENABLE);
    
    OLED_ShowString(1,1,"W:");
    OLED_ShowString(2,1,"R:");
    while(1)
    {
        if(KEY_Get() == 1)
        {
            //д��BKP
            BKP_WriteBackupRegister(BKP_DR1,WriteArr[0]);
            BKP_WriteBackupRegister(BKP_DR2,WriteArr[1]);
            
            //��ʾд���ֵ
            OLED_ShowHexNum(1,3,WriteArr[0],4);
            OLED_ShowHexNum(1,8,WriteArr[1],4);
            
            WriteArr[0]++;
            WriteArr[1]++;
        }
        //��ȡBKP
        ReadArr[0] = BKP_ReadBackupRegister(BKP_DR1);
        ReadArr[1] = BKP_ReadBackupRegister(BKP_DR2);
        //��ʾ��ȡ��ֵ
        OLED_ShowHexNum(2,3,ReadArr[0],4);
        OLED_ShowHexNum(2,8,ReadArr[1],4);
        
    }
}



