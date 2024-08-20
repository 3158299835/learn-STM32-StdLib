#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Store.h"

int main(void)
{   
    //0x1FFFF7E0ΪFLASH ID �Ĵ���λ�ã�����һ��96λ��
    
    OLED_Init();                        //OLED��ʼ��
    
    OLED_ShowString(1, 1, "F_SIZE:");   //��ʾ������
    
    OLED_ShowHexNum(1, 8, *((__IO uint16_t *)(0x1FFFF7E0)), 4);     //ʹ��ָ���ȡָ����ַ�µ� ���������Ĵ���
    
    OLED_ShowString(2, 1, "U_ID:");     //��ʾоƬID��
    
    //ʹ��ָ���ȡָ����ַ�µĲ�ƷΨһ��ݱ�ʶ�Ĵ���
    //�������ֽڡ����֡��ֵķ�ʽ��ȡ
    OLED_ShowHexNum(2, 6, *((__IO uint8_t *)(0x1FFFF7E8)), 2);              //�ֽڶ�������һ���ֽ�        ��0-8λ��
    OLED_ShowHexNum(2, 9, *((__IO uint8_t *)(0x1FFFF7E8) + 1), 2);          //�ֽڶ������ڶ����ֽ�        ��9-16λ��
    OLED_ShowHexNum(2, 12, *((__IO uint16_t *)(0x1FFFF7E8) + 1), 4);        //���ֶ�������3 ��4 ���ֽ�    ��16-32λ��
    OLED_ShowHexNum(3, 1, *((__IO uint32_t *)(0x1FFFF7E8 + 1)), 8);      //��  ������5 6 7 8���ֽ�     ��33-64λ��
    OLED_ShowHexNum(4, 1, *((__IO uint32_t *)(0x1FFFF7E8 + 2)), 8);      //��  ������9 10 11 12���ֽ�  ��64-96λ��
    
    while (1)
    {

    }
}
