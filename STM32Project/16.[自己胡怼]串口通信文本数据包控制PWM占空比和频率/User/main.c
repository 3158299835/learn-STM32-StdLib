#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
#include "PWM.h"
#include "IC.h"
#include "USART.h"

#include "string.h"
/*
    TIM2输出PWM
    TIM3输入捕获
    USART1更改频率和占空比
*/
//提取字符串中的数字
int16_t FerqNum(char* str) 
{
    uint16_t Ferq = 0;  // 用于存储累加的结果
    uint8_t i = 1;//从字符串第二位开始算
    // 当字符不为 '\0' 时进行循环
    while (str[i]!= '\0') 
    {
        if(str[i] < '0' || str[i] > '9')//如果不为\0，但读取到的不是数字。那么退出报错
        {
            return -1;
        }
        if (str[i] >= '0' && str[i] <= '9') //只接收0-9
        {
            if(str[1] == '0')//第一个数字不能为0
            {
                return -2;
            }
            Ferq = Ferq * 10 + (str[i] - '0');  // 累加上当前数字（不是字符形式的）.然后把之前的数字全都往左移（*10）
        }
        i++;
    }

    
    // 如果结果超过 10000 或小于 15，返回 -1
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

//提取字符串中的数字
int16_t DuctNum(char* str) 
{
    int16_t Duct = 0;  // 用于存储累加的结果
    uint8_t i = 1;//从字符串第二位开始算
    // 当字符不为 '\0' 时进行循环
    while (str[i]!= '\0') 
    {
        if(str[i] < '0' || str[i] > '9')//如果不为\0，但读取到的不是数字。那么退出报错
        {
            return -1;
        }
        if (str[i] >= '0' && str[i] <= '9') //只接收0-9
        {
            Duct = Duct * 10 + (str[i] - '0');  // 累加上当前数字（不是字符形式的）.然后把之前的数字全都往左移（*10）
        }
        i++;
    }

    
    // 如果结果超过 100 或小于 0
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







char RXData[100] = { 0 };//存放接收到的数据包
uint8_t RxFlag = 0;//接收到数据包标志位

int main()
{
    OLED_Init();//初始化OLED;
    PWM_Init();
    IC_Init();
    USART1_Init();
    
    PWM_SetFerq(1250);
    PWM_SetDuct(10);
    
    OLED_ShowString(1,1,"Freq:0000HZ");
    OLED_ShowString(2,1,"Duct:00%");
    OLED_ShowString(3,1,"RXStr:");
    OLED_ShowString(4,1,"Cmd:");
    
    USART1_SendString("\n你好，我是PWM调试小助手\n");
    USART1_SendString("输入 @F数字 修改频率\n");
    USART1_SendString("输入 @D数字 修改占空比\n");
    
    int16_t Ferq = 0;
    int16_t Duct = 0;
    
    while(1)
    {
        OLED_ShowNum(1,6,IC_GetFreq(),4);
        OLED_ShowNum(2,6,IC_GetDuct(),2);
        
        //接收到数据包
        if(USART1_GetRxFlag() == 1)
        {
            //显示收到的指令
            OLED_ShowString(3,7,RXData);
            
            //判断并执行命令
            if(RXData[0] == 'F')//判断频率
            {
                Ferq = FerqNum(RXData);//把数据包的数字赋给Ferq
                switch (Ferq)//判断然后报错
                {
                    case -1:{
                        OLED_ShowString(4,5,"Erro:01");
                        USART1_SendString("错误，应该输入数字\n");
                        break;
                    }
                    case -2:{
                        OLED_ShowString(4,5,"Erro:02");
                        USART1_SendString("错误，第一位数字不能为0\n");
                        break;
                    }
                    case -3:{
                        OLED_ShowString(4,5,"Erro:03");
                        USART1_SendString("数字大于10000\n");
                        break;
                    }
                    case -4:{
                        OLED_ShowString(4,5,"Erro:04");
                        USART1_SendString("数字小于15\n");
                        break;
                    }
                }
                if(Ferq >= 0)
                {
                    PWM_SetFerq(Ferq);
                }
            }
            if(RXData[0] == 'D')//判断占空比
            {
                Duct = DuctNum(RXData);//把数据包的数字赋给Duct
                switch (Duct)//判断然后报错
                {
                    case -1:{
                        OLED_ShowString(4,5,"Erro:01");
                        USART1_SendString("错误，应该输入数字\n");
                        break;
                    }
                    case -2:{
                        OLED_ShowString(4,5,"Erro:02");
                        USART1_SendString("错误，第一位数字不能为0\n");
                        break;
                    }
                    case -3:{
                        OLED_ShowString(4,5,"Erro:03");
                        USART1_SendString("数字大于100\n");
                        break;
                    }
                    case -4:{
                        OLED_ShowString(4,5,"Erro:04");
                        USART1_SendString("数字小于0\n");
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


