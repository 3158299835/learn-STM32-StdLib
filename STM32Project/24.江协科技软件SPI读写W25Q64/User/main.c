#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
#include "W25Q64.h"

/**
  * ��    ������֤SPI����W25Q64�洢��
  * ��    ������
  * �� �� ֵ����
  * ע�������
  */

uint8_t ArrWrite[] = {0xAA, 0xBB, 0xCC, 0xDD};
uint8_t ArrRead[4];

int main()
{
    Delay_Init();//��ʼ����ʾ
    OLED_Init();//��ʼ��OLED;
    W25Q64_Init();//��ʼ��W25Q64�洢��

    OLED_ShowString(1,1,"MID:  ,DID:   ");
    
    W25Q64_ReadID(&W25Q64_ID);//��ID�ŵ�����ṹ����
    OLED_ShowHexNum(1,5,W25Q64_ID.MID,2);
    OLED_ShowHexNum(1,12,W25Q64_ID.DID,4);//��ʾMID DID
    
    OLED_ShowString(2,1,"W:");
    OLED_ShowString(3,1,"R:");
    
    W25Q64_PageErase(0x000000);               //������ַ��д��ǰ��Ҫ����ö�λ����������ʼ��ַ������λΪ0����
    W25Q64_PageProgram(0x000000,ArrWrite,4);  //д�����������ݵ��洢��
    W25Q64_ReadData(0x000000,ArrRead,4);      //��ȡ�洢�������ݵ�����
    
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



