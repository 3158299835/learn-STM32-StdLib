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
    OLED_Init();//��ʼ��OLED;
    Delay_Init();//��ʼ����ʱ
    
    MyDMA_Init((uint32_t)DataA,(uint32_t)DataB,4);//��ʼ��DMA
    
    
    //��ʾ��ַ
    OLED_ShowString(1,1,"DataA");
    OLED_ShowHexNum(1, 1, (uint32_t)&DataA, 8);
    
    OLED_ShowString(3,3,"DataB");
    OLED_ShowHexNum(3, 1, (uint32_t)&DataB, 8);

    while(1)
    {
        //��ʾDataA����
        OLED_ShowHexNum(2, 1, DataA[0], 2);
        OLED_ShowHexNum(2, 4, DataA[1], 2);
        OLED_ShowHexNum(2, 7, DataA[2], 2);
        OLED_ShowHexNum(2, 10, DataA[3], 2);
        //��ʱ
        Delay_ms(1000);
        
        //����
        MyDMA_Transfer();
        
        //��ʾDataB����
        OLED_ShowHexNum(4, 1, DataB[0], 2);
        OLED_ShowHexNum(4, 4, DataB[1], 2);
        OLED_ShowHexNum(4, 7, DataB[2], 2);
        OLED_ShowHexNum(4, 10, DataB[3], 2);
        //��ʱ
        Delay_ms(1000);
        //Դ��������
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
//    OLED_Init();//��ʼ��OLED;
//    OLED_ShowHexNum(1,1,SRAM,2);
//    OLED_ShowHexNum(1,4,(uint32_t)&SRAM,8);//��ַ��0x2000 0000 ��ͷ�ġ�λ��RAM���͵������ڴ�SRAM��
//    OLED_ShowHexNum(2,1,Flash,2); 
//    OLED_ShowHexNum(2,4,(uint32_t)&Flash,8);//��ַ��0x0800 0000 ��ͷ�ġ�λ��Flash�У���ֻ���ġ��ŵ�flash���Խ�ʡ�ռ�
//    OLED_ShowHexNum(3,4,(uint32_t)&ADC1->DR, 8); //ADC_DR�Ĵ��������衣������RAM���͵� 0x4000 0000�ϡ������ַ�ǹ̶��ġ�
//    while(1)
//    {
//    }
//}



