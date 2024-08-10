#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
#include "PWM.h"
#include "IC.h"
#include "USART.h"

#include "string.h"
/*
    TIM2���PWM
    TIM3���벶��
    USART1����Ƶ�ʺ�ռ�ձ�
*/
//��ȡ�ַ����е�����
int16_t FerqNum(char* str) 
{
    uint16_t Ferq = 0;  // ���ڴ洢�ۼӵĽ��
    uint8_t i = 1;//���ַ����ڶ�λ��ʼ��
    // ���ַ���Ϊ '\0' ʱ����ѭ��
    while (str[i]!= '\0') 
    {
        if(str[i] < '0' || str[i] > '9')//�����Ϊ\0������ȡ���Ĳ������֡���ô�˳�����
        {
            return -1;
        }
        if (str[i] >= '0' && str[i] <= '9') //ֻ����0-9
        {
            if(str[1] == '0')//��һ�����ֲ���Ϊ0
            {
                return -2;
            }
            Ferq = Ferq * 10 + (str[i] - '0');  // �ۼ��ϵ�ǰ���֣������ַ���ʽ�ģ�.Ȼ���֮ǰ������ȫ�������ƣ�*10��
        }
        i++;
    }

    
    // ���������� 10000 ��С�� 15������ -1
    if (Ferq > 10000) 
    {
        return -3;
    }
    if (Ferq < 15) 
    {
        return -4;
    }

    return Ferq;
}

//��ȡ�ַ����е�����
int16_t DuctNum(char* str) 
{
    int16_t Duct = 0;  // ���ڴ洢�ۼӵĽ��
    uint8_t i = 1;//���ַ����ڶ�λ��ʼ��
    // ���ַ���Ϊ '\0' ʱ����ѭ��
    while (str[i]!= '\0') 
    {
        if(str[i] < '0' || str[i] > '9')//�����Ϊ\0������ȡ���Ĳ������֡���ô�˳�����
        {
            return -1;
        }
        if (str[i] >= '0' && str[i] <= '9') //ֻ����0-9
        {
            Duct = Duct * 10 + (str[i] - '0');  // �ۼ��ϵ�ǰ���֣������ַ���ʽ�ģ�.Ȼ���֮ǰ������ȫ�������ƣ�*10��
        }
        i++;
    }

    
    // ���������� 100 ��С�� 0
    if (Duct > 100) 
    {
        return -3;
    }
    if (Duct < 0) 
    {
        return -4;
    }

    return Duct;
}







char RXData[100] = { 0 };//��Ž��յ������ݰ�
uint8_t RxFlag = 0;//���յ����ݰ���־λ

int main()
{
    OLED_Init();//��ʼ��OLED;
    PWM_Init();
    IC_Init();
    USART1_Init();
    
    PWM_SetFerq(1250);
    PWM_SetDuct(10);
    
    OLED_ShowString(1,1,"Freq:0000HZ");
    OLED_ShowString(2,1,"Duct:00%");
    OLED_ShowString(3,1,"RXStr:");
    OLED_ShowString(4,1,"Cmd:");
    
    USART1_SendString("\n��ã�����PWM����С����\n");
    USART1_SendString("���� @F���� �޸�Ƶ��\n");
    USART1_SendString("���� @D���� �޸�ռ�ձ�\n");
    
    int16_t Ferq = 0;
    int16_t Duct = 0;
    
    while(1)
    {
        OLED_ShowNum(1,6,IC_GetFreq(),4);
        OLED_ShowNum(2,6,IC_GetDuct(),2);
        
        //���յ����ݰ�
        if(USART1_GetRxFlag() == 1)
        {
            //��ʾ�յ���ָ��
            OLED_ShowString(3,7,RXData);
            
            //�жϲ�ִ������
            if(RXData[0] == 'F')//�ж�Ƶ��
            {
                Ferq = FerqNum(RXData);//�����ݰ������ָ���Ferq
                switch (Ferq)//�ж�Ȼ�󱨴�
                {
                    case -1:{
                        OLED_ShowString(4,5,"Erro:01");
                        USART1_SendString("����Ӧ����������\n");
                        break;
                    }
                    case -2:{
                        OLED_ShowString(4,5,"Erro:02");
                        USART1_SendString("���󣬵�һλ���ֲ���Ϊ0\n");
                        break;
                    }
                    case -3:{
                        OLED_ShowString(4,5,"Erro:03");
                        USART1_SendString("���ִ���10000\n");
                        break;
                    }
                    case -4:{
                        OLED_ShowString(4,5,"Erro:04");
                        USART1_SendString("����С��15\n");
                        break;
                    }
                }
                if(Ferq >= 0)
                {
                    PWM_SetFerq(Ferq);
                }
            }
            if(RXData[0] == 'D')//�ж�ռ�ձ�
            {
                Duct = DuctNum(RXData);//�����ݰ������ָ���Duct
                switch (Duct)//�ж�Ȼ�󱨴�
                {
                    case -1:{
                        OLED_ShowString(4,5,"Erro:01");
                        USART1_SendString("����Ӧ����������\n");
                        break;
                    }
                    case -2:{
                        OLED_ShowString(4,5,"Erro:02");
                        USART1_SendString("���󣬵�һλ���ֲ���Ϊ0\n");
                        break;
                    }
                    case -3:{
                        OLED_ShowString(4,5,"Erro:03");
                        USART1_SendString("���ִ���100\n");
                        break;
                    }
                    case -4:{
                        OLED_ShowString(4,5,"Erro:04");
                        USART1_SendString("����С��0\n");
                        break;
                    }
                }
                if(Duct >= 0)
                {
                    PWM_SetDuct(Duct);
                }
            }
            
        
        
            
        }
        
    }
}


