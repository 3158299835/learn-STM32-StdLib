#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "Delay.h"
#include "key.h"
#include "MPU6050.h"
/*
    ָ��6050�豸����ȡ117λ�Ĵ������豸�ţ�
    ��OLED��ʾ����
*/



int main()
{
    OLED_Init();//��ʼ��OLED;
    MPU6050_Init();//��ʼ��MPU6050
    
    
    while(1)    
    {
         MPU6050_GetData(&MPU6050_Data);
        //��ʾ���ٶ�
        OLED_ShowSignedNum(1,1,(int16_t)MPU6050_Data.AccX,5);
        OLED_ShowSignedNum(2,1,(int16_t)MPU6050_Data.AccY,5);
        OLED_ShowSignedNum(3,1,(int16_t)MPU6050_Data.AccZ,5);
        //��ʾ������
        OLED_ShowSignedNum(1,8,MPU6050_Data.GyroX,5);
        OLED_ShowSignedNum(2,8,MPU6050_Data.GyroY,5);
        OLED_ShowSignedNum(3,8,MPU6050_Data.GyroZ,5);
        //��ʾ�¶�
        OLED_ShowSignedNum(4,4,MPU6050_Data.Temp,5);
        
        
    }
    
}





/*���Զ�д�Ĵ���*/
//#include "stm32f10x.h"                  // Device header
//#include "oled.h"
//#include "Delay.h"
//#include "key.h"
//#include "MPU6050.h"
///*
//    ָ��6050�豸����ȡ117λ�Ĵ������豸�ţ�
//    д��Ĵ���������ȡ����������Ƿ���ȷд��
//    ��OLED��ʾ����
//*/

//int main()
//{
//    OLED_Init();//��ʼ��OLED;
//    MPU6050_Init();//��ʼ��MPU6050
//    /*��ȡ0x75�Ĵ����豸�Ų���ʾ*/
//    uint8_t ID = MPU6050_ReadeReg(0x75);
//    OLED_ShowHexNum(1, 1, ID, 2);
//    /*���оƬ˯��ģʽ��������д��*/
//    MPU6050_WriteReg(0x6B,0x00);//���
//    MPU6050_WriteReg(0x19,0xAA);//д��
//    uint8_t Data = MPU6050_ReadeReg(0x19);//����
//    OLED_ShowHexNum(2, 1, Data, 2);//��ʾ
//    MPU6050_WriteReg(0x19,0x66);//д��
//    Data = MPU6050_ReadeReg(0x19);//����
//    OLED_ShowHexNum(3, 1, Data, 2);//��ʾ
//}

/*����I2Cʱ��*/
//#include "stm32f10x.h"                  // Device header
//#include "oled.h"
//#include "Delay.h"
//#include "key.h"
//#include "MyI2C.h"
///*
//    ��ѯ����7λI2C��ַ
//    �ҵ������Ϲ��ص������豸
//    ��OLED��ʾ����
//*/

//int main()
//{
//    OLED_Init();//��ʼ��OLED;
//    MyI2C_Init();//��ʼ��I2C
//    
//    /*
//        �ӻ���ַΪ 1101 000 
//        ���ƺ�0 = 1101 0001 = 0xD0����ʾָ������豸д��
//    */
//    uint8_t Row = 1;
//    uint8_t i = 0x00;
//    for (i = 0x00; i < 0x7F; i++)
//    {
//        MyI2C_Start();//��ʼʱ��
//        MyI2C_SendByte((i << 1) | 0);//�����ֽڡ�дģʽ
//        uint8_t Ack = MyI2C_ReceiveAck();//����Ӧ��
//        MyI2C_Stop();//����ʱ��
//        if(Ack == 0)
//        {
//            OLED_ShowHexNum(Row,1,i,2);
//            OLED_ShowBinNum(Row,4,i,7);
//            Row++;
//        }
//    }
//}



