#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
#include "MPU6050.h"
/*
    指定6050设备，读取117位寄存器（设备号）
    在OLED显示出来
*/



int main()
{
    OLED_Init();//初始化OLED;
    MPU6050_Init();//初始化MPU6050
    
    
    while(1)    
    {
         MPU6050_GetData(&MPU6050_Data);
        //显示加速度
        OLED_ShowSignedNum(1,1,(int16_t)MPU6050_Data.AccX,5);
        OLED_ShowSignedNum(2,1,(int16_t)MPU6050_Data.AccY,5);
        OLED_ShowSignedNum(3,1,(int16_t)MPU6050_Data.AccZ,5);
        //显示陀螺仪
        OLED_ShowSignedNum(1,8,MPU6050_Data.GyroX,5);
        OLED_ShowSignedNum(2,8,MPU6050_Data.GyroY,5);
        OLED_ShowSignedNum(3,8,MPU6050_Data.GyroZ,5);
        //显示温度
        OLED_ShowSignedNum(4,4,MPU6050_Data.Temp,5);
        
        
    }
    
}





/*测试读写寄存器*/
//#include "stm32f10x.h"                  // Device header
//#include "oled.h"
//#include "Delay.h"
//#include "key.h"
//#include "MPU6050.h"
///*
//    指定6050设备，读取117位寄存器（设备号）
//    写入寄存器，并读取出来。检查是否正确写入
//    在OLED显示出来
//*/

//int main()
//{
//    OLED_Init();//初始化OLED;
//    MPU6050_Init();//初始化MPU6050
//    /*读取0x75寄存器设备号并显示*/
//    uint8_t ID = MPU6050_ReadeReg(0x75);
//    OLED_ShowHexNum(1, 1, ID, 2);
//    /*解除芯片睡眠模式，并测试写入*/
//    MPU6050_WriteReg(0x6B,0x00);//解除
//    MPU6050_WriteReg(0x19,0xAA);//写入
//    uint8_t Data = MPU6050_ReadeReg(0x19);//读出
//    OLED_ShowHexNum(2, 1, Data, 2);//显示
//    MPU6050_WriteReg(0x19,0x66);//写入
//    Data = MPU6050_ReadeReg(0x19);//读出
//    OLED_ShowHexNum(3, 1, Data, 2);//显示
//}

/*测试I2C时序*/
//#include "stm32f10x.h"                  // Device header
//#include "oled.h"
//#include "Delay.h"
//#include "key.h"
//#include "MyI2C.h"
///*
//    查询所有7位I2C地址
//    找到总线上挂载的所有设备
//    在OLED显示出来
//*/

//int main()
//{
//    OLED_Init();//初始化OLED;
//    MyI2C_Init();//初始化I2C
//    
//    /*
//        从机地址为 1101 000 
//        左移后补0 = 1101 0001 = 0xD0（表示指定这个设备写）
//    */
//    uint8_t Row = 1;
//    uint8_t i = 0x00;
//    for (i = 0x00; i < 0x7F; i++)
//    {
//        MyI2C_Start();//起始时序
//        MyI2C_SendByte((i << 1) | 0);//发送字节。写模式
//        uint8_t Ack = MyI2C_ReceiveAck();//接收应答
//        MyI2C_Stop();//结束时序
//        if(Ack == 0)
//        {
//            OLED_ShowHexNum(Row,1,i,2);
//            OLED_ShowBinNum(Row,4,i,7);
//            Row++;
//        }
//    }
//}



